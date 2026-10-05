#include "gamelogic.h"
#include <iostream>
#include <fstream>
#include <random>

void GameLogic::greet()
{
    std::cout << "=================================================================================================\n";
    std::cout << R"BANNER(
____ _____ ____    _   _                                         
| __ )_   _/ ___|  | | | | __ _ _ __   __ _ _ __ ___   __ _ _ __  
|  _ \|| |\___ \   | |_| |/ _` | '_ \ / _` | '_ ` _ \ / _` | '_  \ 
| |_) || |  ___) | |  _  | (_| | | | | (_| | | | | | | (_| | | | |
|____/ |_| |____/  |_| |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|
                                    |___/                       
)BANNER";
    std::cout << "Save the BTS members from having to serve their military time so they can keep going on tour!\n";
    std::cout << "Show how much you STAN them by filling in the blanks to correctly guess one of their songs.\n";
    std::cout << "=================================================================================================\n\n";

}

bool GameLogic::loadSongs(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) return false;

    std::string line;

    // read one whole line per call
    while (std::getline(file, line))
    {
        // load a song from file to songs vector if line is not blank
        if (!line.empty())
            songs.push_back(line);
    }

    return !songs.empty(); // return true if songs from file have been loaded to vector
}

std::string GameLogic::pickRandomSong() const
{
    if (songs.empty()) return "";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, songs.size() - 1);

    return songs[dis(gen)];
}

bool GameLogic::checkLetterExist(char letter)
{
    if (board.alreadyTried(letter))
    {
        std::cout << "\nYou've already used '" << letter << "'. Try a different one.\n";
        return true;
    }

    return false;
}

bool GameLogic::isLetterCorrect(char letter)
{
    return board.isCorrect(letter);
}

void GameLogic::playGame()
{
    std::string song = pickRandomSong();
    board.setSecretSong(song);

    while (true) {

        std::cout << "\n";
        board.displayWord();
        board.displayGuessedLetters();
        player.displayMembers();

        char c = player.enterGuess();

        // check if there's already a record of letter
        // start over, no penalty
        if (checkLetterExist(c)) continue;

        if (!isLetterCorrect(c))
        {
            std::string message = player.loseMember();
            std::cout << "\n" << message << "\n";
        }

        // won the game
        if (board.isFullyRevealed())
        {
            std::cout <<"\n";
            board.displayWord();
            std::cout << "BTS will dedicate this song to you on their next tour!\n";
            break;
        }

        // lost the game
        if (player.isGameOver())
        {
            std::cout << "\nGAMEOVER\n";
            std::cout << "The BTS Army is no match for the Military Service Act.\n";
            break;
        }
    }
    
}





