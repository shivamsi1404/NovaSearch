#pragma once

#include <string>
#include <vector>

class Tokenizer {
public:
    // Convert raw text into normalized tokens
    std::vector<std::string> tokenize(const std::string& text);
};