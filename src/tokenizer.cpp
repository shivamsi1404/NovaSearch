#include "tokenizer.h"

// Tokenization is the process of breaking a piece of text into smaller units called tokens.

// control flow 

// we can use string stream to go through the entire sentence and as its nature it parse through words divided by spaces and we can store those in a vector 

// Input text → string stream → extract words → vector of tokens

#include "tokenizer.h"

#include <sstream>

std::vector<std::string> Tokenizer::tokenize(const std::string& text)
{
    std::vector<std::string> tokens;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word)
    {
        tokens.push_back(word);
    }

    return tokens;
}
