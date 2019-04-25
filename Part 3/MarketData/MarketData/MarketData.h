#ifndef MarketData_h
#define MarketData_h

#include <string>
#include <vector>
#include "Stock.h"

using namespace std;

class MarketData 
{
private:
	int iPort;
	string sHost;
	vector<Stock> stockMap;

public:
	bool parseCommandLine(int argc, char** argv);

	void PrintComError(_com_error& e);

	void PrintStockMap();

	void printUsage();

	void run(int argc, char** argv);

	int UpdateTradeDBTable();

};




void MarketData::run(int argc, char** argv)
{
	Service refDataService = session.getService("//blp/refdata");
	Request request = refDataService.createRequest("HistoricalDataRequest");
	request.getElement("fields").appendValue("OPEN");
	request.getElement("fields").appendValue("LAST_TRADE");
	request.getElement("fields").appendValue("VOLUME");
	request.getElement("fields").appendValue("HIGH");
	request.getElement("fields").appendValue("LOW");
	request.set("periodicityAdjustment", "ACTUAL");
	request.set("periodicitySelection", "DAILY");
	request.set("startDate", "20171010");
	request.set("endDate", "20171111");
	request.set("maxDataPoints", 2000);

	vector<string> stockList;
	stockList.push_back("IBM");
	stockList.push_back("MSFT");
	string sSuffix = " US Equity";
	vector<string>::iterator vitr = stockList.begin();
	for (; vitr != stockList.end(); vitr++)
	{
		string sStock = *vitr + sSuffix;
		request.getElement("securities").appendValue(sStock.c_str());
	}
	std::cout << "Sending Request: " << request << std::endl;
	session.sendRequest(request);

	Element securityData = msg.getElement(SECURITY_DATA);
	sSymbol = securityData.getElement("security").getValueAsString();
	std::size_t found = sSymbol.find(" ");
	if (found != std::string::npos)
		sSymbol = sSymbol.substr(0, found);
	Element fieldData = securityData.getElement(FIELD_DATA);
	for (int i = 0; i < int(fieldData.numValues()); i++)
	{
		string sDate = fieldData.getValueAsElement(i).getElement("date").getValueAsString();
		double fClose = fieldData.getValueAsElement(i).getElement("LAST_TRADE").getValueAsFloat64();
		double fOpen = fieldData.getValueAsElement(i).getElement("OPEN").getValueAsFloat64();
		double fHigh = fieldData.getValueAsElement(i).getElement("HIGH").getValueAsFloat64();
		double fLow = fieldData.getValueAsElement(i).getElement("LOW").getValueAsFloat64();
		long lVolume = (long)fieldData.getValueAsElement(i).getElement("VOLUME").getValueAsInt64();
		TradeData aTrade(sDate, fClose, fOpen, fHigh, fLow, lVolume);
		trades.push_back(aTrade);
	}

	if (sSymbol.length() > 0) stockMap.push_back(Stock(sSymbol, trades));

}


int MarketData::UpdateTradeDBTable()
{
	ADODB::_ConnectionPtr pConnect("ADODB.Connection");
	hResult = pConnect->Open(bstrConnect, "admin", "", ADODB::adConnectUnspecified);
	if (SUCCEEDED(hResult))
	{
		char sQuery[256];
		memset((void*)sQuery, '\0', 256);
		sprintf_s(sQuery, "DELETE * FROM DailyData;");
		ADODB::_RecordsetPtr pRecSet("ADODB.Recordset");
		hResult = pRecSet->Open(sQuery, _variant_t((IDispatch *)pConnect, true), ADODB::adOpenUnspecified,
			ADODB::adLockUnspecified, ADODB::adCmdText);

		memset((void*)sQuery, '\0', 256);
		for (vector<Stock>::iterator mIt = stockMap.begin(); mIt != stockMap.end(); mIt++)
		{
			string sSymbol = mIt->getSymbol();
			vector<TradeData> trades = mIt->getTrades();
			for (vector<TradeData>::iterator vIt = trades.begin(); vIt != trades.end(); vIt++)
			{
				string sDate = vIt->getDate();
				double dOpen = vIt->getOpen();
				double dClose = vIt->getClose();
				double dHigh = vIt->getHigh();
				double dLow = vIt->getLow();
				long lVolume = vIt->getVolume();
				sprintf_s(sQuery, "INSERT INTO DailyData VALUES('%s','%s',%.2f,%.2f,%.2f,%.2f,%ld);", sDate.c_str(), sSymbol.c_str(), dOpen, dClose, dHigh, dLow, lVolume);				ADODB::_RecordsetPtr pRecSet("ADODB.Recordset");
				hResult = pRecSet->Open(sQuery, _variant_t((IDispatch *)pConnect, true), ADODB::adOpenUnspecified,
					ADODB::adLockUnspecified, ADODB::adCmdText);
			}
		}
	}
}




#endif // !MarketData_h

