// ========================== PHASE 1 ============================ // 

// Single file test 

#include <iostream>
#include <fstream>
#include <string>

// this version works to find a word in a single file 

using namespace std ;

int main()
{
    ifstream file("../Documents//BatMan.txt"); 

 /*
    ..  means go to parent directory
    /   means go inside a folder
 */


    if(!file)
    {
        cout<<"File Not Found"<<endl;
    }
    else
    {
        cout<<"File Found"<<endl;
    }

    string s;
    cout<<endl;
    cout<<"Enter the text to be searched : ";
    cin>>s;

    string temp; 
    int count = 0 ;

    /*
    
    >> this is used to extract word from the text file 
    
    */

    while(file>>temp)
    {
        if (temp == s)
        {
            count++;
        }
        
    }

    cout<<"Searched Text : "<<s<<"  count : "<<count<<endl;

    file.close();


    return 0 ;
}

/*

With this I conclude the first and the most basic concept of the word search in a file
and mark the end of the Phase 1 . 
With Regards 
Shivam Singh 

*/
