#include "board.h"
#include <iostream>

void Board::setSecretSong(const std::string& song)
{
    secretSong = song;

    // clear guessed letters and hidden word to reset the game initially
    guessedLetters.clear();
    word.clear();

    for (char c: secretSong)
    {
        // if song name has spaces, leave as is
        // else hide it with '_'
        if (c == ' ') word.push_back(' ');
        else          word.push_back('_');
    }
}

bool Board::isCorrect(char letter)
{
    // place letter input by user to set
    guessedLetters.insert(letter);

    // now check if that letter is in word
    bool hit = false;
    for (std::size_t i = 0; i < secretSong.size(); i++)
    {
        if (secretSong[i] == letter)
        {
            word[i] = letter; // reveal every matching position
            hit = true;
        }
    }

    return hit;
}

bool Board::alreadyTried(char letter) const
{
    // if returns 1, then letter is already present == true
    return guessedLetters.count(letter) > 0;
}

bool Board::isFullyRevealed() const
{
    for (char c : word)
    {
        if (c == '_') return false; // any blank left = not solved
    }

    return true;
}

void Board::displayWord() const
{
    std::cout << "Song:  ";
    for (char c : word)
    {
        std::cout << c << ' ';
    }
    std::cout << '\n';
}

void Board::displayGuessedLetters() const
{
    std::cout << "Used:  ";
    for (char c : guessedLetters)
    {
        std::cout << c << ' ';
    }
    std::cout << '\n';
}
