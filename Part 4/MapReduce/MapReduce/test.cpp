//
//  test.cpp
//  MapReduce
//
//  Created by Victor on 2019/5/6.
//  Copyright © 2019 Victor. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int main()
{
    string file_path = "/Users/victor/Desktop/FRE-7831-Big-Data/Part 4/4727.txt";
    
    vector<string> WordList;

    ifstream infile(file_path);
    string line;
    string word;
    getline(infile, line);
        
    istringstream wordStream(line);
    while (getline(wordStream, word, ' '))
    {
        WordList.push_back(word);
    }
    
    cout << WordList.size() << endl;

    return 0;
}
