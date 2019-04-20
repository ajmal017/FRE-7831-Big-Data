//
//  marketdata.cpp
//

#include "marketdata.hpp"
#include "database.hpp"

int PopulatePairTable(sqlite3 *db, const map<int, pair<string, string>> & pairs)
{
    for (map<int, pair<string, string>>::const_iterator itr = pairs.begin(); itr != pairs.end(); itr++)
    {
        char pair_insert_table[512];
        sprintf(pair_insert_table, "INSERT INTO PAIRS (id, symbol1, symbol2) VALUES(%d, \"%s\", \"%s\")", itr->first, itr->second.first.c_str(), itr->second.second.c_str());
        if (InsertTable(pair_insert_table, db) == -1)
            return -1;
    }
    return 0;
}
