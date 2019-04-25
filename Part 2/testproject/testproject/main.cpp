//
//  main.cpp
//  testproject
//
//  Created by Victor on 2019/4/18.
//  Copyright © 2019 Victor. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int main ()
{
//    string file_path("/Users/victor/Desktop/FRE-7831-Big-Data/Lesson 2/Assignment_03/Assignment_03/SPY_May_2012.csv");
//
//    fstream file(file_path);
//    string line;

    
//    char s0[150] = "#RIC,Date[G],Time[G],GMT Offset,Type,Price,Volume,Market VWAP,Bid Price,Bid Size,Ask Price,Ask Size,Qualifiers";
//
//    char s1[150] = "SPY,01-MAY-2012,00:00:00.097,-4,Quote,,,,140.07,1,140.08,3,R  [PRC_QL3];R  [PRC_QL_CD]";
//
//    char s2[150] = "SPY,01-MAY-2012,11:36:55.641,-4,Trade,,,,,,,,\"  T   [GV4_TEXT];131[IRGCOND];NBL[PRC_QL2]\"";
//
//    char ss[150] = "SPY,01-MAY-2012,11:36:55.641,-4,Trade,140.03,100,,,,,,\"  T   [GV4_TEXT];131[IRGCOND];NBL[PRC_QL2]\"";
    
//    int Date;
//    char Time[13];
//    char Type[6];
//    double Price;
//    int Vol;
    
//    sscanf(s2, "%*3s,%2d%*9s,%8s%*4s,%*2s,%5s,%lf,%i,", &Date, Time, Type, &Price, &Vol);
//    cout << Price << endl;
//    cout << Vol << endl;
//
//    sscanf(ss, "%*3s,%2d%*9s,%8s%*4s,%*2s,%5s,%lf,%i,", &Date, Time, Type, &Price, &Vol);
//    cout << Price << endl;
//    cout << Vol << endl;
//
//    sscanf(s2, "%*3s,%2d%*9s,%8s%*4s,%*2s,%5s,%lf,%i,", &Date, Time, Type, &Price, &Vol);
//    cout << Price << endl;
//    cout << Vol << endl;
//
    
    vector<int> Vol_sum; // vector stored all the volume data from May-01 to May-20
    for (int j=0; j<26; j++) // initialize with 0
    {
        Vol_sum.push_back(0);
    }
    
    string t[] = {"09:30:00", "09:45:00", "10:00:00",
        "10:15:00", "10:30:00", "10:45:00", "11:00:00", "11:15:00", "11:30:00",
        "11:45:00", "12:00:00", "12:15:00", "12:30:00", "12:45:00", "13:00:00",
        "13:15:00", "13:30:00", "13:45:00", "14:00:00", "14:15:00", "14:30:00",
        "14:45:00", "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00"
    };
    
//    cout << strcmp("10:30:00.000", "09:30:00.120") << endl;
    
    
    FILE* myfile;
    myfile = fopen ("/Users/victor/Desktop/FRE-7831-Big-Data/Lesson 2/Assignment_03/Assignment_03/SPY_May_2012.csv","r");

    while (!feof(myfile))
    {
//        fscanf(myfile, "%*3s,%2d-MAY-2012,%8s%*4s,-4,%5s,%lf,%i,", &Date, Time, Type, &Price, &Vol);

        int Date;
        char Time[13];
        char Type[6];
        double Price;
        int Vol;

        fscanf(myfile, "%*3s,%2d%*9s,%12s,%*2s,%5s,%lf,%i,", &Date, Time, Type, &Price, &Vol);

        if (strcmp(Type, "Trade") != 0) continue;
        if (strcmp(Time, "09:30:00.000") == -1) continue;

        if (strcmp(Time, "09:45:00.000") == -1) {Vol_sum[0] += Vol; continue;}
        if (strcmp(Time, "10:00:00.000") == -1) {Vol_sum[1] += Vol; continue;}
        if (strcmp(Time, "10:15:00.000") == -1) {Vol_sum[2] += Vol; continue;}
        if (strcmp(Time, "10:30:00.000") == -1) {Vol_sum[3] += Vol; continue;}
        if (strcmp(Time, "10:45:00.000") == -1) {Vol_sum[4] += Vol; continue;}
        if (strcmp(Time, "11:00:00.000") == -1) {Vol_sum[5] += Vol; continue;}
        if (strcmp(Time, "11:15:00.000") == -1) {Vol_sum[6] += Vol; continue;}
        if (strcmp(Time, "11:30:00.000") == -1) {Vol_sum[7] += Vol; continue;}
        if (strcmp(Time, "11:45:00.000") == -1) {Vol_sum[8] += Vol; continue;}
        if (strcmp(Time, "12:00:00.000") == -1) {Vol_sum[9] += Vol; continue;}
        if (strcmp(Time, "12:15:00.000") == -1) {Vol_sum[10] += Vol; continue;}
        if (strcmp(Time, "12:30:00.000") == -1) {Vol_sum[11] += Vol; continue;}
        if (strcmp(Time, "12:45:00.000") == -1) {Vol_sum[12] += Vol; continue;}
        if (strcmp(Time, "13:00:00.000") == -1) {Vol_sum[13] += Vol; continue;}
        if (strcmp(Time, "13:15:00.000") == -1) {Vol_sum[14] += Vol; continue;}
        if (strcmp(Time, "13:30:00.000") == -1) {Vol_sum[15] += Vol; continue;}
        
        if (strcmp(Time, "13:45:00.000") == -1) {Vol_sum[16] += Vol; continue;}
        
        
        if (strcmp(Time, "14:00:00.000") == -1) {Vol_sum[17] += Vol; continue;}
        if (strcmp(Time, "14:15:00.000") == -1) {Vol_sum[18] += Vol; continue;}
        if (strcmp(Time, "14:30:00.000") == -1) {Vol_sum[19] += Vol; continue;}
        if (strcmp(Time, "14:45:00.000") == -1) {Vol_sum[20] += Vol; continue;}
        if (strcmp(Time, "15:00:00.000") == -1) {Vol_sum[21] += Vol; continue;}
        if (strcmp(Time, "15:15:00.000") == -1) {Vol_sum[22] += Vol; continue;}
        if (strcmp(Time, "15:30:00.000") == -1) {Vol_sum[23] += Vol; continue;}
        if (strcmp(Time, "15:45:00.000") == -1) {Vol_sum[24] += Vol; continue;}
        if (strcmp(Time, "16:00:00.000") == -1) {Vol_sum[25] += Vol; continue;}

        if (strcmp("16:00:00.000", Time) == -1) continue;



//        if( feof(myfile) ) break ;
    }

    for (int j=0; j<26; j++)
    {
        cout << t[j] << " ";
        cout << Vol_sum[j]/16 << " ";
        cout << endl;
    }
    
    cout << "finish!" << endl;
    
    
//    cout << Date << endl;
//    cout << Time << endl;
//    cout << Type << endl;
//    cout << Price << endl;
//    cout << Vol << endl;

//    strcpy(Type, "Trade");
//
//    cout << strcmp(Type, "Trade") << endl;
    
//    for (int i=0; i<0; i++)
//    {
//        getline(file, line);
//        cout << line << endl;
//    }
//
//    char s3[150];
//
//    cin >> s3;
//
//    cout << s1 << endl;
//    cout << s2 << endl;
//
//    cout << s3 << endl;

    return 0;
}
