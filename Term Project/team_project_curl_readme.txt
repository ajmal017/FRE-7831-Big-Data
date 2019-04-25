			for (set<string>::const_iterator itr = pairSymbols.begin(); itr != pairSymbols.end(); itr++)
				{
					string readBuffer;
					string stock_url_common = "https://eodhistoricaldata.com/api/eod/";
					string stock_start_date = "2008-01-01";
					string stock_end_date = "2018-12-31";
					string api_token = "5ba84ea974ab42.45160048";
					string pair_stock_retrieve_url = stock_url_common + *itr + ".US?" +
						"from=" + stock_start_date + "&to=" + stock_end_date + "&api_token=" + api_token + "&period=d";
					if (RetrieveMarketData(pair_stock_retrieve_url, readBuffer) == -1)
						return -1;
					
					cout << readBuffer

				}