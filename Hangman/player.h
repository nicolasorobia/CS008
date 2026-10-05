#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <set>
#include <utility>

class Player
{
private:
    // each member of BTS acts as lives
    std::vector<std::pair<std::string, std::string>> members
    {
        {"RM",       "RM changed his name to AM because he'll have to wake up early for boot camp."},
        {"Jin",      "Jin needs a djinn to wish himself out of this."},
        {"Suga",     "Suga woulda shoulda coulda."},
        {"J-Hope",   "J-Hope hoped he didn't have to serve."},
        {"Jimin",    "Jimin needed a minute to process this."},
        {"V",        "V said this is very very sad."},
        {"Jungkook", "Jungkook is cooked."}
    };

public:
    Player() = default;

    char enterGuess();
    std::string loseMember();
    bool isGameOver() const;

    void displayMembers() const;
};

#endif

/*
    Player Properties:
    - Lives
    - Letters player has guessed in current round

    Player Functionalities:
    - Prompt to return keyboard input for lowercase letter ONLY
    - Tracks lives
*/