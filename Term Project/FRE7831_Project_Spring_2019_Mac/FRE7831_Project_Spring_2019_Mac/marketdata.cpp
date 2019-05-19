//
//  marketdata.cpp
//

#include "marketdata.hpp"
#include "database.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int RetrieveMarketData(string url_request, string & read_buffer)
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL * myHandle;
	CURLcode result;
	myHandle = curl_easy_init();

	curl_easy_setopt(myHandle, CURLOPT_URL, url_request.c_str());

	//adding a user agent
	curl_easy_setopt(myHandle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 6.1; rv:2.2) Gecko/20110201");
	curl_easy_setopt(myHandle, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(myHandle, CURLOPT_SSL_VERIFYHOST, 0);
	//curl_easy_setopt(myHandle, CURLOPT_VERBOSE, 1);

	// send all data to this function  
	curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteCallback);

	// we pass our 'chunk' struct to the callback function 
	curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, &read_buffer);

	//perform a blocking file transfer
	result = curl_easy_perform(myHandle);

	// check for errors 
	if (result != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
		return -1;
	}
	curl_easy_cleanup(myHandle);
	return 0;
}

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
