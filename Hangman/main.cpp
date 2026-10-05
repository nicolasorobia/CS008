#include "board.h"
#include "player.h"
#include "gamelogic.h"
#include <iostream>

int main()
{
    GameLogic hangman;
    hangman.greet();

    if (!hangman.loadSongs("bts_songs.txt"))
    {
        std::cerr << "Could not load file\n"
                  << "Run the program from the folder that contains it.\n";
        return 1;
    }

    hangman.playGame();

    return 0;
}