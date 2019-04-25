//
//  main.cpp
//  Assignment_03
//
//  Created by Victor on 2019/4/16.
//  Copyright © 2019 Victor. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>

// #RIC,Date[G],Time[G],GMT Offset,Type,Price,Volume,Market VWAP,Bid Price,Bid Size,Ask Price,Ask Size,Qualifiers



using namespace std;

int main()
{
    
    string file_path = "/Users/victor/Desktop/FRE-7831-Big-Data/Lesson 2/Assignment_03/Assignment_03/SPY_May_2012.csv";
    
    fstream file(file_path);
    string line;
    
//    vector<vector<string>> datatable;
    
    
    string timeinterval[27] = {"09:30:00", "09:45:00", "10:00:00",
        "10:15:00", "10:30:00", "10:45:00", "11:00:00", "11:15:00", "11:30:00",
        "11:45:00", "12:00:00", "12:15:00", "12:30:00", "12:45:00", "13:00:00",
        "13:15:00", "13:30:00", "13:45:00", "14:00:00", "14:15:00", "14:30:00",
        "14:45:00", "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00"
    };

    unordered_map<string, double> datamap;
    for (int j=0; j<26; j++)
    {
        datamap[timeinterval[j]] = 0.0;
    }
    
    vector<int> vol_data; // vector stored all the volume data from May-01 to May-20
    for (int j=0; j<26; j++) // initialize with 0
    {
        vol_data.push_back(0);
    }
    
    vector<double> price_data; //vector stored all first trade price data in each interval on May-21
    for (int j=0; j<26; j++) // initialize with 0.0
    {
        price_data.push_back(0.0);
    }
    
    
//    for (int i=0; i<2000; i++)
    while (getline(file, line, '\n'))
    {
//        getline(file, line);
        stringstream ss(line);
        
        vector<string> row;
        string data;
        
        while (getline(ss, data, ','))
        {
            row.push_back(data);
        }
        
        if (row[2]>="09:30:00" && row[2]<="16:00:00" && row[4]=="Trade" && row[6]!="")
        {
            if (row[1].substr(0,2)=="21")
            {
                for (int k=0; k<26; k++)
                {
                    if (price_data[k]==0.0)
                    {
                        if (row[2]>=timeinterval[k] && row[2]<timeinterval[k+1])
                        {
                            price_data[k] = price_data[k] + stod(row[5]);
                            break;
                        }
                    }

                }
            }
            else
            {
                for (int k=0; k<26; k++)
                {
                    if (row[2]>=timeinterval[k] && row[2]<timeinterval[k+1])
                    {
                        vol_data[k] = vol_data[k] + stoi(row[6]);
                        //                    cout << vol_data[k] << endl;
                        break;
                    }
                }
            }
        }
    }
    
    for (int j=0; j<26; j++)
    {
        cout << timeinterval[j] << " ";
        cout << vol_data[j]/16 << " ";
        cout << price_data[j] << endl;
    }

    
//
////    for (int i=0; i<8000; i++)
//    while (getline(file, line, '\n'))
//    {
////        getline(file, line);
//        stringstream ss(line);
////        cout << line << endl;
//        vector<string> row;
//        string data;
//
//        while (getline(ss, data, ','))
//        {
//            row.push_back(data);
//        }
//
//        if (row[2]>="09:30:00" && row[2]<="16:00:00" && row[4]=="Trade" && row[6]!="")
//        {
//            for (int k=0; k<26; k++)
//            {
//                if (row[2]>=timeinterval[k] && row[2]<timeinterval[k+1])
//                {
//                    datamap[timeinterval[k]] = datamap[timeinterval[k]] + stod(row[6]);
////                    cout << datamap[timeinterval[k]] << endl;
//                    break;
//                }
//            }
////            cout << line << endl;
//        };
//    }
//
//    for (int i=0; i<26; i++)
//    {
//        cout << datamap[timeinterval[i]] << endl;
//    }
//


    
//    string s = "100.20";
//
//    cout << datamap[timeinterval[0]] << endl;
//
//    cout << stod(s) << endl;
//
//    datamap[timeinterval[0]] += stod(s);
//
//    cout << datamap[timeinterval[0]] << endl;

    

//
////    for (int i=0; i<10; i++)
////    {
////        getline(file, line);
////        cout << line << endl;
////    }
//
//    while (getline(file, line, '\n'))
//    {
//
//        stringstream ss(line);
//        //put it in a stringstream
//
//        vector<string> row;
//        string data;
//
//        // read (string) items up to a comma
//        while (getline(ss, data, ','))
//        {
//            row.push_back(data);
//            // put all data in a row vector
//        }
//
//
//        // date: row[1]
//        // time: row[2]
//        // price: row[5]
//        // volume: row[6]
//
//        if (row[4] == "Trade")  // only "Trade" rows will be considered
//        {
//            for (int k=0; k<26; k++)
//            {
//                if (row[2]>=timeinterval[k] && row[2]<timeinterval[k+1])
//                {
//                    datamap[timeinterval[k]] = datamap[timeinterval[k]] + stod(row[6]);
//                    break;
//                }
//            }
//        }
//    }


    

//    while ( getline( file, line, '\n' ) ) // read a whole line of the file
//    {
//        stringstream ss( line );
//        //put it in a stringstream
//
//        vector<string> row;
//        string data;
//
//        // read (string) items up to a comma
//        while ( getline( ss, data, ',' ) )
//        {
//            row.push_back( data );
//            // put all data in a row vector
//        }
//
//        if ( row[5] == "Trade" ) datatable.push_back( row );
//        // add "Trade" rows to matrix
//    }

    
    
    return 0;
}
