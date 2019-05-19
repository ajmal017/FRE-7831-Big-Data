#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun May 12 12:13:49 2019

@author: victor
"""

import json
import datetime as dt
import urllib.request
import pandas as pd
import numpy as np

from sqlalchemy import Column, Integer, Float, String
from sqlalchemy import create_engine
from sqlalchemy import MetaData
from sqlalchemy import Table
from sqlalchemy import inspect

requestURL = "https://eodhistoricaldata.com/api/eod/"
myEodKey = "5ba84ea974ab42.45160048"

k = 1

startDate = dt.datetime(2018,1,1) # all the data we pull
endDate = dt.datetime(2019,1,31)

model_start = dt.datetime(2018,1,1) # time range for building model
model_end = dt.datetime(2018,12,31)

backtest_start = dt.datetime(2018,12,31) # time range for backtesting
backtest_end = dt.datetime(2019,1,31)

def get_daily_data(symbol, start=startDate, end=endDate, requestType=requestURL, apiKey=myEodKey):
    symbolURL = str(symbol) + ".US?"
    startURL = "from=" + str(start)
    endURL = "to=" + str(end)
    apiKeyURL = "api_token=" + myEodKey
    completeURL = requestURL + symbolURL + startURL + '&' + endURL + '&' + apiKeyURL + '&period=d&fmt=json'
#     print(completeURL)
    with urllib.request.urlopen(completeURL) as req:
        data = json.load(req)
        return data

def clear_a_table(table_name, metadata, engine):
    conn = engine.connect()
    table = metadata.tables[table_name]
    delete_st = table.delete()
    conn.execute(delete_st)

def execute_sql_statement(sql_st, engine):
    result = engine.execute(sql_st)
    return result

def create_pair_table(name, metadata, engine): # Create Pair1Stocks & Pair2Stocks table
	tables = metadata.tables.keys()            # date ranging from 2018/1/1-2019/1/31
	if name not in tables:
		table = Table(name, metadata, 
					Column('symbol', String(50), primary_key=True, nullable=False),
					Column('date', String(50), primary_key=True, nullable=False),
					Column('open', Float, nullable=False),
					Column('high', Float, nullable=False),
					Column('low', Float, nullable=False),
					Column('close', Float, nullable=False),
                       Column('adjusted_close', Float, nullable=False),
					Column('volume', Integer, nullable=False))
		table.create(engine)
        
def create_pairprices_table(name, metadata, engine): # Create PairPrices table only containing backtesting data
    tables = metadata.tables.keys()                  # this table is pulled from Pair1Stocks and Pair2Stocks
    if name not in tables:
        table = Table(name, metadata, 
					Column('ticker1', String(50), primary_key=True, nullable=False),
					Column('ticker2', String(50), primary_key=True, nullable=False),
					Column('date', String(50), primary_key=True, nullable=False),
					Column('open1', Float, nullable=False),
					Column('close1', Float, nullable=False),
					Column('open2', Float, nullable=False),
					Column('close2', Float, nullable=False))
        
        table.create(engine)

def create_trades_table(name, metadata, engine): # Create Trades table
    tables = metadata.tables.keys()              # it stores PnL of every trades
    if name not in tables:
        table = Table(name, metadata, 
					Column('ticker1', String(50), primary_key=True, nullable=False),
					Column('ticker2', String(50), primary_key=True, nullable=False),
					Column('date', String(50), primary_key=True, nullable=False),
					Column('profit_loss', Float, nullable=False))
        
        table.create(engine)
        
def create_pairs_table(name, metadata, engine): # Create Pairs table
    tables = metadata.tables.keys()             # it stores volatility and total PnLs of all pairs we test
    if name not in tables:
        table = Table(name, metadata, 
                        Column('ticker1', String(50), primary_key=True, nullable=False),
                        Column('ticker2', String(50), primary_key=True, nullable=False),
                        Column('volatility', Float, nullable=False),
                        Column('profit_loss', Float, nullable=False))

        table.create(engine)

def populate_stock_data(tickers, metadata, engine, table_name): # After creating all 5 tables
    conn = engine.connect()                                     # pull data from website 
    table = metadata.tables[table_name]                         # and populate the Pair1Stocks and Pair2Stocks
    for ticker in tickers:                                      # this function only runs twice
        stock = get_daily_data(ticker)                          # once for Pair1Stocks, once for Pair2Stocks
#         print(stock)
        for stock_data in stock:
            #print(k, v)
            trading_date = stock_data['date']
            trading_open = stock_data['open']
            trading_high = stock_data['high']
            trading_low = stock_data['low']
            trading_close = stock_data['close']
            trading_adjusted_close = stock_data['adjusted_close']
            trading_volume = stock_data['volume']
            insert_st = table.insert().values(symbol=ticker, date=trading_date,
					open = trading_open, high = trading_high, low = trading_low,
					close = trading_close, adjusted_close = trading_adjusted_close, 
                       volume = trading_volume)
            conn.execute(insert_st)

def build_pair_trading_model(tickers): # building model and calculating the volatility of first pair
    
    s = model_start.strftime('%Y-%m-%d')
    e = model_end.strftime('%Y-%m-%d')
    
    sql_st = '''
SELECT Pair1Stocks.adjusted_close, Pair2Stocks.adjusted_close 
FROM Pair1Stocks, Pair2Stocks 
WHERE ((Pair1Stocks.date >= \'{}\') AND (Pair1Stocks.date <= \'{}\') AND (Pair1Stocks.date = Pair2Stocks.date) AND (Pair1Stocks.symbol = \'{}\') AND (Pair2Stocks.symbol = \'{}\'))
'''.format(s, e, tickers[0], tickers[1])
    
    result = execute_sql_statement(sql_st, engine)
    adj_close = np.array(result.fetchall())
    pr = adj_close[:,0] / adj_close[:,1]
    vol = np.std(pr)
    
    return vol

def populate_pairprices_table(tickers, metadata, engine): # start preparing data for backtesting of first pair
    conn = engine.connect()                               # pull data from Pair1Stocks and Pair2Stocks
    table = metadata.tables['PairPrices']
    
    s = backtest_start.strftime('%Y-%m-%d')
    e = backtest_end.strftime('%Y-%m-%d')
    
    sql_st = '''
SELECT Pair1Stocks.symbol, Pair2Stocks.symbol, Pair1Stocks.date, Pair1Stocks.open, Pair1Stocks.close, Pair2Stocks.open, Pair2Stocks.close 
FROM Pair1Stocks, Pair2Stocks 
WHERE ((Pair1Stocks.date >= \'{}\') AND (Pair1Stocks.date <= \'{}\') AND (Pair1Stocks.date = Pair2Stocks.date) AND (Pair1Stocks.symbol = \'{}\') AND (Pair2Stocks.symbol = \'{}\'))
''' .format(s, e, tickers[0], tickers[1])
    
    result = execute_sql_statement(sql_st, engine)
    
    for r in result:
        insert_st = table.insert().values(ticker1=r[0], ticker2=r[1], date=r[2],
					open1 = r[3], close1 = r[4],
					open2 = r[5], close2 = r[6])
    
        conn.execute(insert_st)

def backtesting(tickers): # backtesting every trades
                          # and return a table of the PnL of every trade and total PnL
    sql_st = '''
SELECT * FROM PairPrices
WHERE ((ticker1 = \'{}\') AND (ticker2 = \'{}\'))
'''.format(tickers[0], tickers[1])
    result = execute_sql_statement(sql_st, engine)
    
    PairPrices = pd.DataFrame(result.fetchall(), 
                columns=['ticker1', 'ticker2', 'date', 'open1', 'close1', 'open2', 'close2'])
    
    PnL = []

    for i in range(1, len(PairPrices)):

        diff = abs( PairPrices.loc[i-1, 'close1'] / PairPrices.loc[i-1, 'close2'] \
        - PairPrices.loc[i, 'open1'] / PairPrices.loc[i, 'open2'] )

        if diff >= k*vol:
            # short the pair
            N1 = 10000
            N2 = (-N1) * ( PairPrices.loc[i, 'open1'] / PairPrices.loc[i, 'open2'] )
            # close the trade and calculate PnL
            r = N1 * ( PairPrices.loc[i, 'open1'] - PairPrices.loc[i, 'close1'] ) \
                + N2 * ( PairPrices.loc[i, 'open2'] - PairPrices.loc[i, 'close2'] )

        elif diff < k*vol:
            # long the pair
            N1 = -10000
            N2 = (-N1) * ( PairPrices.loc[i, 'open1'] / PairPrices.loc[i, 'open2'] )
            # close the trade and calculate PnL
            r = N1 * ( PairPrices.loc[i, 'open1'] - PairPrices.loc[i, 'close1'] ) \
                + N2 * ( PairPrices.loc[i, 'open2'] - PairPrices.loc[i, 'close2'] )

        PnL.append(r)
        
    PnL.insert(0,0)
    PairPrices['PnL'] = PnL
    Trades = PairPrices.loc[:, ['ticker1', 'ticker2', 'date', 'PnL']]
    total_PnL = sum(PnL)
    return Trades, total_PnL

def populate_trades_table(tickers, metadata, engine): # populate the Trades table
    conn = engine.connect()                           # with the PnL we obtain from bactesting
    table = metadata.tables['Trades']
    
    for i in range(len(Trades)):
        
        trading_date = Trades.loc[i, 'date']
        pnl = Trades.loc[i, 'PnL']
        
        insert_st = table.insert().values(ticker1=tickers[0], ticker2=tickers[1], date=trading_date,
					profit_loss = pnl)
    
        conn.execute(insert_st)

def populate_pairs_table(tickers, metadata, engine): # populate the pairs table
    conn = engine.connect()                          # with the volatility from moedelbuilding                       
    table = metadata.tables['Pairs']                 # and total PnL from backtesting
                    
    insert_st = table.insert().values(ticker1=tickers[0], ticker2=tickers[1], volatility=vol,
				profit_loss = total_PnL)
    
    conn.execute(insert_st)
    
# Create Database
engine = create_engine('sqlite:///:memory:')
metadata = MetaData(engine)

# Create all 5 tables
create_pair_table('Pair1Stocks', metadata, engine)
create_pair_table('Pair2Stocks', metadata, engine)
create_pairprices_table('PairPrices', metadata, engine)
create_trades_table('Trades', metadata, engine)
create_pairs_table('Pairs', metadata, engine)

# read all the pairs
ticker_pairs = pd.read_csv('PairTrading.csv')

# populate the Pair1Stocks and Pair2Stocks tables
pair1_list = list(set(ticker_pairs['Ticker1']))
pair2_list = list(set(ticker_pairs['Ticker2']))

print('Pulling data from {}'.format(requestURL))
populate_stock_data(pair1_list, metadata, engine, 'Pair1Stocks')
populate_stock_data(pair2_list, metadata, engine, 'Pair2Stocks')


for t1, t2 in zip(ticker_pairs['Ticker1'], ticker_pairs['Ticker2']):
    tickers = [t1, t2]
    
    # build pair trading model
    # return the volatility
    print('Building model of pair: {} and {}'.format(tickers[0], tickers[1]))
    vol = build_pair_trading_model(tickers)
    print('volatility is {}'.format(vol))
    
    # prepare the trading data of a pair for backtesting
    populate_pairprices_table(tickers, metadata, engine)
    
    # backtesting
    # return a table of PnL of every trades and total PnL
    print('Running backtesting ')
    Trades, total_PnL = backtesting(tickers)
    print('Total PnL is {}'.format(total_PnL))
    
    # populate the Trades table with the Trades table from backtesting
    populate_trades_table(tickers, metadata, engine)
    
    # populate the Pairs table
    # with volatility from model building and total PnL from backtesting
    populate_pairs_table(tickers, metadata, engine)
    print('------------------------------------------\n')
    

sql_st = 'SELECT * FROM Pairs'
result = execute_sql_statement(sql_st, engine)

print(result.fetchall())
