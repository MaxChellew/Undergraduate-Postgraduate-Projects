############################# Title #############################

''' Data analysis functions '''

############################ Settings ###########################

''' Install Libarys '''
import pandas as pd
import numpy as np

#################### Data Anyalsis functions ####################

''' Transform Function (price) '''
def transform(x,        # Insert Data
              freq,     # Insert time interval i.e. 1m >>> "1T", 5m >>> "5T" ect
              usecol):  # Insert Pricing coloum (Open, High, Low, CLose, Adjusted close)
    ##   Note: This function turns the csv file of  into a NxM matrix where n is 
    ##   the number of trading days and m is the number of price bars per day
    #   Find start and end Index of data frame
    sd = np.min(x.index)
    ed = np.max(x.index)
    #   create date (in days) and time (in 15m intervals) indexing for data frame
    date_index = pd.date_range(start=sd, end=ed, freq='D') #create a date index series
    time_index = pd.date_range(start=pd.to_datetime('14:30:00', format="%H:%M:%S"), end=pd.to_datetime('20:55:00', format="%H:%M:%S"), freq=freq)
    #   Create NxM matrix
    x_dates = np.array(list(map(lambda x : x.date(),x.index)))
    x_mat = pd.DataFrame(index=date_index,columns=time_index.time)
    #   Fill NxM with 
    for d in date_index:
        day1_ind = (x_dates==d.date()) #find all index (boolean) on d
        if np.sum(day1_ind)>0:
            day1_x = x.Close[day1_ind]
        for i in list(range(0, len(time_index))):
            x_mat.loc[d,time_index.time[i]] = day1_x[i]
    return x_mat

''' Transform Function (Volume) '''
def transformVol(x,        # Insert Data
              freq,     # Insert time interval i.e. 1m >>> "1T", 5m >>> "5T" ect
              usecol):  # Insert Pricing coloum (Open, High, Low, CLose, Adjusted close)
    ##   Note: This function turns the csv file of  into a NxM matrix where n is 
    ##   the number of trading days and m is the number of price bars per day
    #   Find start and end Index of data frame
    sd = np.min(x.index)
    ed = np.max(x.index)
    #   create date (in days) and time (in 15m intervals) indexing for data frame
    date_index = pd.date_range(start=sd, end=ed, freq='D') #create a date index series
    time_index = pd.date_range(start=pd.to_datetime('14:30:00', format="%H:%M:%S"), end=pd.to_datetime('20:55:00', format="%H:%M:%S"), freq=freq)
    #   Create NxM matrix
    x_dates = np.array(list(map(lambda x : x.date(),x.index)))
    x_mat = pd.DataFrame(index=date_index,columns=time_index.time)
    #   Fill NxM with 
    for d in date_index:
        day1_ind = (x_dates==d.date()) #find all index (boolean) on d
        if np.sum(day1_ind)>0:
            day1_x = x.Volume[day1_ind]
        for i in list(range(0, len(time_index))):
            x_mat.loc[d,time_index.time[i]] = day1_x[i]
    return x_mat