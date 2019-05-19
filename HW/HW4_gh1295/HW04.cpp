// HW04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <blpapi_session.h>
#include <blpapi_eventdispatcher.h>

#include <blpapi_event.h>
#include <blpapi_message.h>
#include <blpapi_element.h>
#include <blpapi_name.h>
#include <blpapi_request.h>
#include <blpapi_subscriptionlist.h>
#include <blpapi_defs.h>
#include <blpapi_exception.h>

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <utility>
#include <tchar.h>

#include "MarketData.h"
#include "TradeData.h"
#include "Stock.h";

using  namespace BloombergLP;
using  namespace blpapi;
using namespace std;

int main(int argc, char** argv)
{

	MarketData example;
	example.run(argc, argv);
	example.PrintStockMap();
	example.UpdateTradeDBTable();

	return 0;
}

