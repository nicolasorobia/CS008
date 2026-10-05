#include "player.h"
#include <iostream>
#include <cctype> // easy built in functionality for checks

char Player::enterGuess()
{
    std::string userInput;
    char c;
    while (true)
    {
        std::cout << "Guess a letter (a - z): ";
        std::getline(std::cin, userInput);

        if (userInput.length() == 1)
        {
            c = userInput[0];
            c = std::tolower(c);
            if (c >= 'a' && c <= 'z') return c;
        }
        
        // if invalid, try again
        std::cout << "Please enter a single letter that's from a - z only.\n";
    }
}

std::string Player::loseMember()
{
    // store the message associated with BTS member that will be deleted
    std::string message = members.back().second;
    members.pop_back();
    return message;
}

bool Player::isGameOver() const
{
    // true if no members left
    return members.empty();
}

void Player::displayMembers() const
{
    std::cout << "Members left (" << members.size() << "):  ";
    for (const auto& name: members)
    {
        std::cout << name.first << " ";
    }
    std::cout << "\n";
}