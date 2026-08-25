#include <iostream>
#include <fstream>

#include  "../include/storage.h"

int main()
{
    // Sample Inverted Index
    unordered_map<string, vector<pair<int, int>>> index;

    index["batman"] = {
        {1, 5},
        {2, 3},
        {4, 1}
    };

    index["thor"] = {
        {2, 7},
        {5, 2}
    };

    index["ironman"] = {
        {1, 4},
        {3, 8}
    };

    index["joker"] = {
        {4, 6}
    };

    // Save the index
    SaveIndex(index);

    cout << "Index saved successfully!\n";

    return 0;
}