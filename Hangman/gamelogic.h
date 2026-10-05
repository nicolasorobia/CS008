#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "board.h"
#include "player.h"
#include <vector>
#include <string>
#include <set>

class GameLogic
{
private:
    Board board;
    Player player;
    std::vector<std::string> songs;
    
public:
    void greet();
    bool loadSongs(const std::string& filename);
    std::string pickRandomSong() const;
    
    bool checkLetterExist(char letter);
    bool isLetterCorrect(char letter);
    void playGame();
};

#endif

/*
    Game Logic Properties:
    - Holds Board & Player object (NOT INHERIT)
    - Word Bank (BTS SONGS)
    - Rules, how many wrong guesses are allowed, and what ends a round

    Game Logic Functionalities:
    - Load the word list from file
    - Check for repeated guesses
    - Check if board reveals letters or take a life
*/