
#include "tokenizer.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    Tokenizer tokenizer;

    // Test 1: Basic tokenization and lowercase conversion
    {
        const std::string input = "THIS IS a TEST";
        const std::vector<std::string> expected = {
            "this", "is", "a", "test"
        };

        assert(tokenizer.tokenize(input) == expected);
    }

    // Test 2: Punctuation removal
    {
        const std::string input = "Hello, wor!ld. C++";
        const std::vector<std::string> expected = {
            "hello", "world", "c"
        };

        assert(tokenizer.tokenize(input) == expected);
    }

    // Test 3: Repeated whitespace
    {
        const std::string input = "NovaSearch    is\tfast\n";
        const std::vector<std::string> expected = {
            "novasearch", "is", "fast"
        };

        assert(tokenizer.tokenize(input) == expected);
    }

    // Test 4: Empty input
    {
        const std::string input = "";
        const std::vector<std::string> expected = {};

        assert(tokenizer.tokenize(input) == expected);
    }

    // Test 5: Punctuation-only tokens
    {
        const std::string input = "!!! ... ???";
        const std::vector<std::string> expected = {};

        assert(tokenizer.tokenize(input) == expected);
    }

    // Test 6: Numbers
    {
        const std::string input = "NovaSearch 2.0 has 100 docs";
        const std::vector<std::string> expected = {
            "novasearch", "20", "has", "100", "docs"
        };

        assert(tokenizer.tokenize(input) == expected);
    }

    std::cout << "All tokenizer tests passed!\n";

    return 0;
}
