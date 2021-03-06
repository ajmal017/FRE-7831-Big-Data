#ifndef Stock_h
#define Stock_h

#include <string>
#include <vector>
#include "TradeData.h"

using namespace std;
class Stock
{
private:
	string sSymbol;
	vector<TradeData> trades;

public:
	void addTrade(const TradeData& trade){trades.push_back(trade);}

	string getSymbol() { return sSymbol; }

	const vector<TradeData>& getTrades() { return trades; }

	Stock operator=(const Stock&stock) {
		sSymbol = stock.sSymbol;
		trades = stock.trades;
	}

	Stock() {};


	Stock(const Stock& stock) {
		sSymbol = stock.sSymbol;
		trades = stock.trades;
	}

	Stock(string sSymbol_, const vector<TradeData> trades_): sSymbol(sSymbol_),trades(trades_) {}

	void print()
	{
		cout << sSymbol << endl;
		for (vector<TradeData>::iterator it = trades.begin(); it != trades.end(); ++it)
			it->print();
	}

};


#endif // !Stock_h
