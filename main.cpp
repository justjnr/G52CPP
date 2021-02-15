#include <ctime>
#include <cctype>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const string arrAlphabet[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
string arrModAlphabet[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"}, sCurrentWord, sCurrentWordObfs;
vector<string> vecWordList;
ifstream fileWords;
int intGuessesLeft = 6, intLettersGuessed = 0, intWordLength = 0;
char cInputLetter, cRestartLetter = 'y';
bool bWordMatched, bLetterChosen;

void readFile(){
    string fileLine;
    while (getline(fileWords, fileLine))
    {
        vecWordList.push_back(fileLine);
    }
}

string getAlphabet(){
    string cA = "";
    for (int i = 0; i < 26; i++){
        cA.append(arrModAlphabet[i]);
    }
    return cA;
}

void getRandWord(){
    sCurrentWord = vecWordList[rand() % (ssize_t)vecWordList.size()];
    /*for (std::vector<string>::const_iterator i = vecWordList.begin(); i != vecWordList.end(); ++i)
        std::cout << *i << ' ';*/
}

string getObfuscatedWord(){
    for (char& c : sCurrentWord){
        intWordLength ++;
        sCurrentWordObfs.append("-");
    }
    return sCurrentWordObfs;
}

void matchInput(char a){
    bWordMatched = bLetterChosen = false;
    for (int i = 0; i < (ssize_t)sizeof(arrAlphabet)/(ssize_t)sizeof(*arrAlphabet); i++){
        if (arrModAlphabet[i][0] == '.' && arrAlphabet[i][0] == a){
            bLetterChosen = true;
            cout << "\n!!! Letter " << a << " already chosen !!!\n\n";
        }
        else if (a == arrModAlphabet[i][0])
        {
            arrModAlphabet[i] = ".";
            for (int i = 0; i < (ssize_t)sCurrentWord.size(); i++){
                if (a == sCurrentWord[i]){
                    sCurrentWordObfs[i] = a;
                    intLettersGuessed++;
                    bWordMatched = true;
                }
            }
        }
    }
    if (bWordMatched){
        cout << "\n*** Correct guess - " << a << " is in the word ***\n\n";
    } else if (!bLetterChosen){
        cout << "\n!!! Incorrect guess - " << a << " is not in the word !!!\n\n";
        intGuessesLeft--;
    }
}

void initGame(){
    intGuessesLeft = 6;
    intLettersGuessed = 0;
    sCurrentWordObfs = "";
    sCurrentWord = "";
    intWordLength = 0;
    for (int i = 0; i < (ssize_t)sizeof(arrAlphabet)/(ssize_t)sizeof(*arrAlphabet); i++){
        arrModAlphabet[i] = arrAlphabet[i];
    }
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    if (argc == 2){
        fileWords.open(argv[1]);
        if (fileWords.fail()){
            cout << "Error Opening File\n\n";
        }
        initGame();
        readFile();
        getRandWord();
        getObfuscatedWord();
    } else {
        fileWords.open("wordlist.txt");
        if (fileWords.fail()){
            cout << "Error Opening File\n\n";
        }
        initGame();
        readFile();
        getRandWord();
        getObfuscatedWord();
    }
    while (cRestartLetter == 'Y' || cRestartLetter == 'y') {
        while (intGuessesLeft > 0 && intLettersGuessed < intWordLength) {
            cout << "Guess a letter for the word: " << sCurrentWordObfs << "\n";
            cout << "You have " << intGuessesLeft << " guesses left and have guessed " << intLettersGuessed << " letters out of " << intWordLength << " so far.\n";
            cout << "Available letters are: " << getAlphabet() << "\n\n";
            cin >> cInputLetter;
            matchInput(tolower(cInputLetter));
        }
        if (intLettersGuessed == intWordLength){
            cout << "\n*** Well done, you guessed the word '" << sCurrentWord << "' & finished with " << intGuessesLeft << " guesses left ***\n";
            cout << "Have Another Go? (Y/N)\n";
            cin >> cRestartLetter;
            if (cRestartLetter == 'Y' || cRestartLetter == 'y'){
                initGame();
                getRandWord();
                getObfuscatedWord();
            } else {
                return 0;
            }
        }
        if (intGuessesLeft == 0){
            cout << "\n!!! Out of guesses, the word was '" << sCurrentWord << "' !!!\n";
            cout << "Try Again? (Y/N)\n";
            cin >> cRestartLetter;
            if (cRestartLetter == 'Y' || cRestartLetter == 'y'){
                initGame();
                getRandWord();
                getObfuscatedWord();
            } else {
                return 0;
            }
        }
    }
}