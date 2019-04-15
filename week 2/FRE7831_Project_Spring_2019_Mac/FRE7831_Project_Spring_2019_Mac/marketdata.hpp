//
//  marketdata.hpp
//

#ifndef marketdata_hpp
#define marketdata_hpp

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <unistd.h>
#include <iomanip>

#include "curl/curl.h"
#include "database.hpp"

using namespace std;

int RetrieveMarketData(string url_request);
int PopulateStockTable(sqlite3 *db, string symbol);
int PopulatePairTable(sqlite3 *db, const map<int, pair<string, string>> & symbols);

#endif /* marketdata_hpp */
