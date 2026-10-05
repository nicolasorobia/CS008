#include <iostream>
#include <string>

bool isPalindrome(const std::string& str)
{
    const char *begin = str.data();
    const char *end = str.data() + str.length() - 1;

    while (begin < end)
    {
        // skip spaces/punctuations when iterating through begin & end pointers
        while (begin < end && !std::isalnum(*begin))            begin++;
        while (begin < end && !std::isalnum(*end))              end--;

        // compare the characters & ignore uppercase
        if (std::tolower(*begin) != std::tolower(*end))         return false;

        begin++;
        end--;
    }

    return true;
}

int main()
{
    std::string str1 = "Never odd or even";
    std::string str2 = "Run it back";

    std::cout << std::boolalpha;
    std::cout << "Is '" << str1 << "' a palindrome: " << isPalindrome(str1) << std::endl;
    std::cout << "Is '" << str2 << "' a palindrome: " << isPalindrome(str2) << std::endl;   

    return 0;
}