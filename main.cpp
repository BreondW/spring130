#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// function to check if a letter is in the word
bool isLetterInWord(char letter, string word) {
    for (int i = 0; i < word.length(); i++) {
        if (letter == word[i]) {
            return true;
        }
    }
    return false;
}

// function to update the display of the word with correctly guessed letters
void updateWordDisplay(char letter, string word, string& wordDisplay) {
    for (int i = 0; i < word.length(); i++) {
        if (letter == word[i]) {
            wordDisplay[i] = letter;
        }
    }
}

// function to get a random word from a category
string getRandomWord(vector<string> categoryWords) {
    int index = rand() % categoryWords.size();
    return categoryWords[index];
}

int main() {
    // seed the random number generator
    srand(time(NULL));

    // initialize the categories and words
    vector<string> animalWords = {"cat", "dog", "fox"};
    vector<string> colorWords = {"red", "blue", "tan"};
    vector<string> fruitWords = {"fig", "kiwi", "pea"};

    // initialize variables for the game
    vector<string> usedWords;
    bool playAgain = true;
    while (playAgain) {
        // initialize variables for the game
        vector<string> usedWords;
        bool validChoice = false;
        string chosenWord;
        while (!validChoice) {
            cout << "Choose a category number: " << endl;
            cout << "1. Animals" << endl;
            cout << "2. Colors" << endl;
            cout << "3. Fruits" << endl;

            int categoryChoice;
            cin >> categoryChoice;

            switch (categoryChoice) {
                case 1:
                    chosenWord = getRandomWord(animalWords);
                    validChoice = true;
                    break;
                case 2:
                    chosenWord = getRandomWord(colorWords);
                    validChoice = true;
                    break;
                case 3:
                    chosenWord = getRandomWord(fruitWords);
                    validChoice = true;
                    break;
                default:
                    cout << "Invalid choice, try again." << endl;
                    break;
            }
        }

        // initialize variables for the game
        int incorrectGuesses = 0;
        string wordDisplay(chosenWord.length(), '_');

        // game loop for guessing the word
        while (incorrectGuesses < 6) {
            // display the word display and the number of incorrect guesses
            cout << "Word: " << wordDisplay << endl;
            cout << "Incorrect guesses: " << incorrectGuesses << "/6" << endl;

            // get the user's guess
            char guess;
            cout << "Enter a letter guess: ";
            cin >> guess;

            // check if the guess has already been made
            bool isAlreadyGuessed = false;
            for (string word : usedWords) {
                if (isLetterInWord(guess, word)) {
                    isAlreadyGuessed = true;
                    break;
                }
            }
            if (isAlreadyGuessed) {
                cout << "You already guessed that letter. Try again." << endl;
                continue;
            }

            // add the guess to the list of used words
            usedWords.push_back(string(1, guess));

            // check if the guess is in the word
            if (isLetterInWord(guess, chosenWord)) {
                // correct guess, update the word display
                updateWordDisplay(guess, chosenWord, wordDisplay);

                // check if the word has been guessed
                if (wordDisplay == chosenWord) {
                    cout << "Congratulations, you guessed the word!" << endl;
                    break;
                }
            } else {
                // incorrect guess, increase the number of incorrect guesses
                incorrectGuesses++;
                cout << "Incorrect guess, try again." << endl;

                // check if the player has lost
                if (incorrectGuesses == 6) {
                    cout << "Sorry, you lost. The word was " << chosenWord << "." << endl;
                }
            }
        }

        // ask the player if they want to play again
        cout << "Do you want to play again? (y/n): ";
        char playAgainChoice;
        cin >> playAgainChoice;
        playAgain = (playAgainChoice == 'y' || playAgainChoice == 'Y');

        // clear the list of used words for the next game
        usedWords.clear();
    }

    // game over

        cout << "Thanks for playing!" << endl;
        
        return 0;
    }

