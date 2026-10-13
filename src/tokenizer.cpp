#include "tokenizer.h"

// Tokenization is the process of breaking a piece of text into smaller units called tokens.

// control flow

// we can use string stream to go through the entire sentence and as its nature it parse through words divided by spaces and we can store those in a vector

// Input text → string stream → extract words → vector of tokens

// next process is to remove the punctuations from entire sentence

#include <sstream>

#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string &text)
{
    std::vector<std::string> tokens;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word)
    {
        std::string normalized;

        for (unsigned char ch : word)
        {
            if (std::isalnum(ch))
            {
                normalized += static_cast<char>(std::tolower(ch));
            }

            // std::tolower(ch) converts an uppercase character to lowercase, if applicable. It returns an int, not a char.

            // static_cast<char>(...) explicitly converts that returned integer into a char.
        }

        if (!normalized.empty())
        {
            tokens.push_back(normalized);
        }
    }

    return tokens;
}
