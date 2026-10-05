#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <set>
#include <vector>

class Board
{
private:
    std::string secretSong;
    std::set<char> guessedLetters;
    std::vector<char> word;

public:
    Board() = default;

    // assign a song from file to be used in game
    void setSecretSong(const std::string& song);
    // debugger function
    std::string getSecretSong() const { return secretSong; }

    bool isCorrect(char letter);
    bool alreadyTried(char letter) const;
    bool isFullyRevealed() const;

    // display contents for Hangman Game
    void displayWord() const;
    void displayGuessedLetters() const;

};

#endif

/*
    Board Properties:
    - Contain secret word for current round
    - Visible state of word in positions revealed + blanks
    - Keep a record of every letter guessed

    Board Functionalities:
    - Accept a secret word and reset function
    - Report when given letter has already been tried
    - Report when entire word is revealed
    - Reveal correct position of guessed letter
    - Draws itself
*/