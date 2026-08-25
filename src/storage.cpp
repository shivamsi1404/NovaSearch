#include <iostream>
#include <fstream>

#include  "../include/storage.h"

void SaveIndex(unordered_map<string,vector<pair<int,int>>>&index)
{
    ofstream outfile("../LocalStorage/index.txt");

    if(!outfile)
    {
        cout<<"failed to open"<<endl;
        return;
    }

    for (const auto &entry : index)
    {
        outfile<<entry.first<<endl;

        for (const auto &entrytwo : entry.second)
        {
            outfile<<entrytwo.first<<":"<<entrytwo.second<<endl;
        }

        outfile<<"END"<<endl;
    }

    outfile.close();
}

