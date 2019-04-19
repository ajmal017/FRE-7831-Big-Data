//
//  test.cpp
//  Assignment_03
//
//  Created by Victor on 2019/4/19.
//  Copyright © 2019 Victor. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    string s1("10:00:00");
    string s2("09:45:13.345");

    vector<int> v1;
    v1.push_back(10);
    
    cout << (s1<s2) << endl;
    cout << v1[0] << endl;
    
    return 0;
}
