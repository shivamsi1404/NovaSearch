#pragma once

// pragma once allows prevention of multiple header files in document 

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void SaveIndex(unordered_map<string,vector<pair<int,int>>>&index);

void LoadIndex(unordered_map<string,vector<pair<int,int>>>&index);
