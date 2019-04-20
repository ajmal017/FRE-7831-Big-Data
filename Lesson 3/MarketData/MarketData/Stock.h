//
//  Stock.h
//  
//
//  Created by Victor on 2019/4/20.
//

#ifndef Stock_h
#define Stock_h

#include<string>
#include<vector>

using namespace std;
class Stock
{
private:
    string sSymbol;
    vector<TradeData> trades;
    
public:
    void addTrade(const TradeData& trade)
    {
        trades.push_back(trade);
    }
    
    string getsymbol()
    {
        return sSymbol;
    }
    
    const vector<TradeData>& getTrades()
    {
        return trades;
    }
    
    Stock operator=(const Stock&stock)
    {
        this->sSymbol = stock.sSymbol;
        this->trades = stock.trades;
    }
    
    Stock(){}
    
    Stock(const Stock& stock)
    {
        sSymbol = stock.sSymbol;
        trades = stock.trades;
    }
    
    Stock(string sSymbol_, const vector<TradeData> trades_):sSymbol(sSymbol_),trades(trades_){}
    
    
    
};



#endif /* Stock_h */
