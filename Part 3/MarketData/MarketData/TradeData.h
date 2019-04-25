#ifndef TradeData_h
#define TradeData_h

#include <string>

using namespace std;


class TradeData
{
private:
	double dClose;
	double dHigh;
	double dLow;
	double dOpen;

	long lVolume;

	string sDate;

public:
	double getClose() { return dClose; }
	string getDate() { return sDate; }
	double getHigh() { return dHigh; }
	double getLow() { return dLow; }
	double getOpen() { return dOpen; }
	long getVolume() { return lVolume; }

	TradeData operator=(const TradeData& TrDa) {
		dClose = TrDa.dClose;
		dHigh = TrDa.dHigh;
		dLow = TrDa.dLow;
		dOpen = TrDa.dOpen;
		lVolume = TrDa.lVolume;
		sDate = TrDa.sDate;
	}

	TradeData();

	TradeData(const TradeData& TrDa) {
		dClose = TrDa.dClose;
		dHigh = TrDa.dHigh;
		dLow = TrDa.dLow;
		dOpen = TrDa.dOpen;
		lVolume = TrDa.lVolume;
		sDate = TrDa.sDate;
	}
	TradeData(string sDate_, double dOpen_, double dClose_, double dHigh_, double dLow_, long lVolume_) {
		dClose = dClose_;
		dHigh = dHigh_;
		dLow = dLow_;
		dOpen = dOpen_;
		lVolume = lVolume_;
		sDate = sDate_;
	}

};



#endif // !TradeData_h

