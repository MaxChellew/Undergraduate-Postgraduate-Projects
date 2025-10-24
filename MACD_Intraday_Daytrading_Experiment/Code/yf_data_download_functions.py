############################# Title #############################

''' Merge and Download Functions '''

############################ Settings ###########################

''' Install Libarys '''
import pandas as pd
import numpy as np
import os as os
import yfinance as yf

########################### Functions ###########################

''' Merge Data Function '''
def merge_data(file1,   # Instert File 1 (csv file)
               file2):  # Instert File 2 (csv file)
    #   Read file1 and file2 as dataframe; merge to df to extend historical 
    #   data records
    df1 = pd.read_csv(file1,index_col='Datetime',parse_dates=['Datetime'])
    df2 = pd.read_csv(file2,index_col='Datetime',parse_dates=['Datetime'])
    df = pd.merge(df1,df2,how='outer',left_index=True, right_index=True)
    #   File formating
    ind = np.sum(np.isnan(df.iloc[:,:6]),axis=1).values==6
    df.iloc[ind,:6] = df.iloc[ind,6:]
    df = df.iloc[:,:6]
    df.columns=df1.columns
    return df

''' Downlaod and Save csv Files Function '''
def download(sd,            # Insert start dates ([...], datetime)
             ed,            # Insert end dates ([...], datetime)
             interval,      # Insert time interval (int)
             no_periods,    # Inster number of periods start and end dates span over (int)
             tickers,       # Insert stock ticker ([...])
             file_names):   # Instert file Names ([...])
    ##   Note: Valid intervals: [1m, 2m, 5m, 15m, 30m, 60m, 90m, 1h, 1d, 5d,
    ##   1wk, 1mo, 3mo] with historical  1-min data (30 days max), historical
    ##   5-min data (60 days max) and historical 15-min data (60 days max)
    for i in range(0, len(tickers)):
        #   Downlaod first pair of data and set to csv file
        df_n = yf.download(tickers=tickers[i], start=sd[0], end=ed[0], interval=interval)
        df_n.to_csv("dummy_n.csv")
        df_nplus1 = yf.download(tickers=tickers[i], start=sd[1], end=ed[1], interval=interval)
        df_nplus1.to_csv("dummy_nplus1.csv")
        #   Merging first pair of data and set to csv file
        df_n = merge_data("dummy_n.csv", "dummy_nplus1.csv")
        df_n.to_csv("dummy_n.csv")
        #   Checking if periods is greater than 2 then next line of code needs to run
        if no_periods > 2:
            for j in range(2, no_periods):
                #   Downlaod next lot of data and set to scv file
                df_nplus1 = yf.download(tickers=tickers[i], start=sd[j], end=ed[j], interval=interval)
                df_nplus1.to_csv("dummy_nplus1.csv")
                # merging next pair of data and set to scv file
                df_n = merge_data("dummy_n.csv", "dummy_nplus1.csv")
                df_n.to_csv("dummy_n.csv")
        #   Save final csv file
        df_n.to_csv(file_names[i])
    os.remove("dummy_n.csv")
    os.remove("dummy_nplus1.csv")
    
######################### Download Data ########################
## run only if new data is to be downloaded (remove # to run) ##

''' Import required Libary '''
#from datetime import datetime

''' Setting Work-directory '''
#os.chdir(os.path.dirname(os.path.realpath(__file__)))

''' Set variables '''
#sd = [datetime(2023,1,23), datetime(2023,1,30), datetime(2023,2,6), datetime(2023,2,13), datetime(2023,2,20), datetime(2023,2,27), datetime(2023,3,6), datetime(2023,3,13)]
#ed = [datetime(2023,1,28), datetime(2023,2,4), datetime(2023,2,11),datetime(2023,2,18), datetime(2023,2,25), datetime(2023,3,4), datetime(2023,3,11), datetime(2023,3,18)]
#interval = "5m"
#no_periods = int(8)
#tickers = ["TSLA", "NVDA", "GOOG"]
#file_names = ["TSLA_5m.csv", "NVDA_5m.csv", "GOOG_5m.csv"]

''' Download Data '''
#download(sd,ed,interval,no_periods,tickers,file_names)
