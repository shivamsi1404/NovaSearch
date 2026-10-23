#include "tokenizer.h"

#include <cctype>
#include <sstream>

// Tokenization is the process of breaking text into smaller units called tokens.
//
// Control flow:
// Input text -> string stream -> extract words -> normalize -> vector of tokens
//
// Normalization:
// 1. Remove punctuation and non-alphanumeric characters.
// 2. Convert uppercase characters to lowercase.
// 3. Ignore empty tokens.

std::vector<std::string> Tokenizer::tokenize(const std::string& text)
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
        }

        if (!normalized.empty())
        {
            tokens.push_back(normalized);
        }
    }

    return tokens;
}