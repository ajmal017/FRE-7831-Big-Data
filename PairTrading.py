# -*- coding: utf-8 -*
#!/usr/bin/env python3

import json
import datetime as dt
import urllib.request
import pandas as pd
import numpy as np

from sqlalchemy import Column, ForeignKey, Integer, Float, String
from sqlalchemy import and_, or_, not_
from sqlalchemy import create_engine
from sqlalchemy import MetaData
from sqlalchemy import Table
from sqlalchemy import inspect
from flask import Flask, flash, redirect, render_template, request, url_for

location_of_pairs = 'csv/PairTrading.csv'

app = Flask(__name__)

engine = create_engine('sqlite:///PairTrading.db')
conn = engine.connect()
conn.execute("PRAGMA foreign_keys = ON")

metadata = MetaData()
metadata.reflect(bind=engine)
    
start_date = dt.date(2018, 1, 1)
end_date = dt.datetime.now()
    
back_testing_start_date = "2018-12-31"
back_testing_end_date = "2019-01-31"
k = 1
    
def get_daily_data(symbol, 
                   start=dt.datetime(2018,12,1), 
                   end=dt.date.today(), 
                   requestURL='https://eodhistoricaldata.com/api/eod/', 
                   apiKey='5ba84ea974ab42.45160048'):
    symbolURL = str(symbol) + '.US?'
    startURL = 'from=' + str(start)
    endURL = 'to=' + str(end)
    apiKeyURL = 'api_token=' + apiKey
    completeURL = requestURL + symbolURL + startURL + '&' + endURL + '&' + apiKeyURL + '&period=d&fmt=json'
    print(completeURL)
    with urllib.request.urlopen(completeURL) as req:
        data = json.load(req)
        return data

def create_stockpairs_table(table_name, metadata, engine):
    table = Table(table_name, metadata,
                  Column('Ticker1', String(50), primary_key=True, nullable=False),
                  Column('Ticker2', String(50), primary_key=True, nullable=False),
                  Column('Volatility', Float, nullable=False),
                  Column('Profit_Loss', Float, nullable=False),
                  extend_existing=True)
    table.create(engine)
                       
def create_pair_table(table_name, metadata, engine):
    .....
    .....

def create_pairprices_table(table_name, metadata, engine):
    ....
    ....

def create_trades_table(table_name, metadata, engine):
    ....
    ....
    
def clear_a_table(table_name, metadata, engine):
    conn = engine.connect()
    table = metadata.tables[table_name]
    delete_st = table.delete()
    conn.execute(delete_st)

def execute_sql_statement(sql_st, engine):
    result = engine.execute(sql_st)
    return result

def populate_stock_data(tickers, engine, table_name, start_date, end_date):
    ....
    ....
        

def build_pair_trading_model(metadata, engine, start_date, end_date, back_testing_start_date):
    ....
    ....

class StockPair:

    def __init__(self, symbol1, symbol2, volatility, k, start_date, end_date):
        self.ticker1 = symbol1
        self.ticker2 = symbol2
        self.volatility = volatility
        self.k = k
        self.start_date = start_date
        self.end_date = end_date
        self.trades = {}
        self.total_profit_loss = 0.0
        
    def __str__(self):
        return str(self.__class__) + ": " + str(self.__dict__) + "\n"
    
    def __repr__(self):
        return str(self.__class__) + ": " + str(self.__dict__) + "\n"
    
    def createTrade(self, date, open1, close1, open2, close2, qty1 = 0, qty2 = 0, profit_loss = 0.0):
        self.trades[date] = np.array([open1, close1, open2, close2, qty1, qty2, profit_loss])
        
    def updateTrades(self):
        trades_matrix = np.array(list(self.trades.values()))
        for index in range(1, trades_matrix.shape[0]):
            if abs(trades_matrix[index-1, 1]/trades_matrix[index-1, 3] - trades_matrix[index, 0]/trades_matrix[index, 2])   \
                > self.k * self.volatility:
                trades_matrix[index, 4] = -10000
                trades_matrix[index, 5] = int(10000 * (trades_matrix[index, 0]/trades_matrix[index, 2]))
            else:
                trades_matrix[index, 4] = 10000
                trades_matrix[index, 5] = int(-10000 * (trades_matrix[index, 0]/trades_matrix[index, 2]))
            trades_matrix[index, 6] = trades_matrix[index, 4] * (trades_matrix[index, 1] - trades_matrix[index, 0])     \
                                    + trades_matrix[index, 5] * (trades_matrix[index, 3] - trades_matrix[index, 2])
            trades_matrix[index, 6] = round(trades_matrix[index, 6], 2)
            
            self.total_profit_loss += trades_matrix[index, 6]
            
        for key, index in zip(self.trades.keys(), range(0, trades_matrix.shape[0])):
            self.trades[key] = trades_matrix[index]
            
        return pd.DataFrame(trades_matrix[:, range(4, trades_matrix.shape[1])], columns=['Qty1', 'Qty2', 'P/L'])

def back_testing(metadata, engine, k, back_testing_start_date, back_testing_end_date):
    ....
    ...
    
        
@app.route('/')
def index():
    pairs = pd.read_csv(location_of_pairs)
    pairs = pairs.transpose()
    list_of_pairs = [pairs[i] for i in pairs]
    return render_template("index.html", pair_list=list_of_pairs)

@app.route('/build_model')
def build_model():
    build_pair_trading_model(metadata, engine, start_date, end_date, back_testing_start_date)
    
    select_st = "Select * from PairPrices;"
    result_set = execute_sql_statement(select_st, engine)
    result_df = pd.DataFrame(result_set.fetchall())
    result_df.columns = result_set.keys()
    result_df = result_df.transpose()
    list_of_pairs = [result_df[i] for i in result_df]
    return render_template("build_model.html", pair_list=list_of_pairs)

@app.route('/back_test')
def model_back_testing():
    back_testing(metadata, engine, k, back_testing_start_date, back_testing_end_date)
    
    select_st = "Select * from Pairs;"
    result_set = execute_sql_statement(select_st, engine)
    result_df = pd.DataFrame(result_set.fetchall())
    result_df.columns = result_set.keys()
    result_df['Volatility'] = result_df['Volatility'].map('{:.4f}'.format)
    result_df['Profit_Loss'] = result_df['Profit_Loss'].map('${:,.2f}'.format)
    result_df = result_df.transpose()
    list_of_pairs = [result_df[i] for i in result_df]
    return render_template("back_testing.html", pair_list=list_of_pairs)

.....
.....
    
if __name__ == "__main__":
    app.run()

    

    
    
    
