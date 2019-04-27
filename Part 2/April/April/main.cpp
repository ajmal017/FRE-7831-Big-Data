//
//  main.cpp
//  April
//
//  Created by Victor on 2019/4/21.
//  Copyright © 2019 Victor. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

int main(int argc, const char * argv[]) {
    
    string file_path = "/Users/victor/Desktop/FRE-7831-Big-Data/Part 2/Assignment_03/Assignment_03/SPY_May_2012.csv";
    
    fstream file(file_path);
    string line;
    
    int Vol_sum[26];
    for (int j=0; j<26; j++)
    {
        Vol_sum[j] = 0;
    }
    
    
    string t[] = {"09:30:00", "09:45:00", "10:00:00",
        "10:15:00", "10:30:00", "10:45:00", "11:00:00", "11:15:00", "11:30:00",
        "11:45:00", "12:00:00", "12:15:00", "12:30:00", "12:45:00", "13:00:00",
        "13:15:00", "13:30:00", "13:45:00", "14:00:00", "14:15:00", "14:30:00",
        "14:45:00", "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00"
    };
    
    
    while ( getline( file, line, '\n' ) )
    {
        stringstream ss( line );
        vector<string> row;
        string data;
    
        while ( getline( ss, data, ',' ) )
        {
            row.push_back( data );
        }
        
//        cout << line << endl;
//
//        if (row[4] == "Trade" && row[2] >= "13:30:00.000" && row[2] <= "13:45:00.000" )
//            cout << row[1] << " " << row[2] << " " << row[4] << " " << row[5] << " " << row[6] << endl;
        
        if (row[4] != "Trade") continue;
        if (row[2] < t[0]) continue;
        
        if (row[2] < t[1]) {Vol_sum[0] += stoi(row[6]); continue;}
        if (row[2] < t[2]) {Vol_sum[1] += stoi(row[6]); continue;}
        if (row[2] < t[3]) {Vol_sum[2] += stoi(row[6]); continue;}
        if (row[2] < t[4]) {Vol_sum[3] += stoi(row[6]); continue;}
        if (row[2] < t[5]) {Vol_sum[4] += stoi(row[6]); continue;}
        if (row[2] < t[6]) {Vol_sum[5] += stoi(row[6]); continue;}
        if (row[2] < t[7]) {Vol_sum[6] += stoi(row[6]); continue;}
        if (row[2] < t[8]) {Vol_sum[7] += stoi(row[6]); continue;}
        if (row[2] < t[9]) {Vol_sum[8] += stoi(row[6]); continue;}
        if (row[2] < t[10]) {Vol_sum[9] += stoi(row[6]); continue;}
        if (row[2] < t[11]) {Vol_sum[10] += stoi(row[6]); continue;}
        if (row[2] < t[12]) {Vol_sum[11] += stoi(row[6]); continue;}
        if (row[2] < t[13]) {Vol_sum[12] += stoi(row[6]); continue;}
        if (row[2] < t[14]) {Vol_sum[13] += stoi(row[6]); continue;}
        if (row[2] < t[15]) {Vol_sum[14] += stoi(row[6]); continue;}
        if (row[2] < t[16]) {Vol_sum[15] += stoi(row[6]); continue;}
        if (row[2] < t[17]) {Vol_sum[16] += stoi(row[6]); continue;}
        if (row[2] < t[18]) {Vol_sum[17] += stoi(row[6]); continue;}
        if (row[2] < t[19]) {Vol_sum[18] += stoi(row[6]); continue;}
        if (row[2] < t[20]) {Vol_sum[19] += stoi(row[6]); continue;}
        if (row[2] < t[21]) {Vol_sum[20] += stoi(row[6]); continue;}
        if (row[2] < t[22]) {Vol_sum[21] += stoi(row[6]); continue;}
        if (row[2] < t[23]) {Vol_sum[22] += stoi(row[6]); continue;}
        if (row[2] < t[24]) {Vol_sum[23] += stoi(row[6]); continue;}
        if (row[2] < t[25]) {Vol_sum[24] += stoi(row[6]); continue;}
        if (row[2] < t[26]) {Vol_sum[25] += stoi(row[6]); continue;}

        if (row[2] >= t[26]) continue;
        
    }
    
    for (int j=0; j<26; j++)
    {
        cout << t[j] << " ";
        cout << Vol_sum[j]/16 << " ";
        cout << endl;
    }
    
    
    
    
}
