############################# Title #############################

''' Backtest functions '''

############################ Settings ###########################

''' Install Libarys '''
import numpy as np
import pandas as pd
import os as os

''' Setting Work-directory '''
os.chdir(os.path.dirname(os.path.realpath(__file__)))

''' Import functions '''
import technical_indicator_functions as tech

####################### Backtest Functions ######################

''' Count number of trades function '''
def cntTrades(signal):  # insert signal (long, Short)
    #find the number of trades in each day
    change_position = signal.copy().diff(axis=1)
    if (np.sum(signal.values>0)>0) and (np.sum(signal.values<0)==0):
        #long only strategy
        return np.sum(change_position>0,axis=1)
    if (np.sum(signal.values<0)>0) and (np.sum(signal.values>0)==0):
        #short only strategy
        return np.sum(change_position<0,axis=1)

''' Total return function '''
def calTotRtn(p,        # instert price matrix
              signal):  # insert signal (long, Short)
    #   find the number of trades in each day
    change_position = signal.copy().diff(axis=1)
    ret = np.zeros(p.shape[0])
    if (np.sum(signal.values>0)>0) and (np.sum(signal.values<0)==0):
        #long only strategy
        ind_in = np.where((change_position==1).values)
        ind_out = np.where((change_position==-1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            for j in range(0,len(p_in)):
                p_out[j] = np.log(p_out[j])
                p_in[j] = np.log(p_in[j])
            ret[i] = np.sum(p_out-p_in)
        return ret
    if (np.sum(signal.values<0)>0) and (np.sum(signal.values>0)==0):
        #short only strategy
        ind_in = np.where((change_position==-1).values)
        ind_out = np.where((change_position==1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            for j in range(0,len(p_in)):
                p_out[j] = np.log(p_out[j])
                p_in[j] = np.log(p_in[j])
            ret[i] = np.sum(p_out-p_in)
        return ret

''' Standard Devation of Returns  '''
def calStdRtn(p,        # instert price matrix
              signal):  # insert signal (long, Short)
    #   find the number of trades in each day
    change_position = signal.copy().diff(axis=1)
    std = np.zeros(p.shape[0])
    if (np.sum(signal.values>0)>0) and (np.sum(signal.values<0)==0):
        #long only strategy
        ind_in = np.where((change_position==1).values)
        ind_out = np.where((change_position==-1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            for j in range(0,len(p_in)):
                p_out[j] = np.log(p_out[j])
                p_in[j] = np.log(p_in[j])
            std[i] = np.std(p_out-p_in)
        return std
    if (np.sum(signal.values<0)>0) and (np.sum(signal.values>0)==0):
        #short only strategy
        ind_in = np.where((change_position==-1).values)
        ind_out = np.where((change_position==1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            for j in range(0,len(p_in)):
                p_out[j] = np.log(p_out[j])
                p_in[j] = np.log(p_in[j])
            std[i] = np.std(p_out-p_in)
        return std
    
''' Sharpe Ratio Function'''
def sharpeRatio(p,         # instert price matrix
                signal):   # insert signal (long, Short)
    return (calTotRtn(p, signal)/cntTrades(signal))/calStdRtn(p, signal)

''' Total Profits and losses '''
def PnL(p,          # instert price matrix
        signal):    # insert signal (long, Short)
    #   find the number of trades in each day
    change_position = signal.copy().diff(axis=1)
    ret = np.zeros(p.shape[0])
    if (np.sum(signal.values>0)>0) and (np.sum(signal.values<0)==0):
        #   long only strategy
        ind_in = np.where((change_position==1).values)
        ind_out = np.where((change_position==-1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            ret[i] = np.sum(p_out-p_in)
        return ret
    if (np.sum(signal.values<0)>0) and (np.sum(signal.values>0)==0):
        #   short only strategy
        ind_in = np.where((change_position==-1).values)
        ind_out = np.where((change_position==1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            ret[i] = np.sum(p_out-p_in)
        return ret
    
''' Win ratio Function '''
def winRatio(p,         # instert price matrix
             signal):   # insert signal (long, Short)
    #   find the number of trades in each day
    change_position = signal.copy().diff(axis=1)
    ret = np.zeros(p.shape[0])
    if (np.sum(signal.values>0)>0) and (np.sum(signal.values<0)==0):
        #   long only strategy
        ind_in = np.where((change_position==1).values)
        ind_out = np.where((change_position==-1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            ret[i] = np.sum((p_out-p_in)>0)/len(p_in)
        return ret
    if (np.sum(signal.values<0)>0) and (np.sum(signal.values>0)==0):
        #   short only strategy
        ind_in = np.where((change_position==-1).values)
        ind_out = np.where((change_position==1).values)
        for i in np.arange(p.shape[0]):
            p_in=p.values[i,ind_in[1][ind_in[0]==i]]
            p_out=p.values[i,ind_out[1][ind_out[0]==i]]
            ret[i] = np.sum((p_out-p_in)>0)/len(p_in)
        return ret
    
''' Backtest matrix '''
def backtestMatrix(p,               # Insert price matrix
                   windows,         # Insert Look-back windows (short_term window, long_term window, Signal window)
                   signal_type):    # Insert signal ("Long", "Short)
    #   Create empty backtest dataframe
    cols = ['Num.Obs.', 'Num.Trade', 'Tot.Ret', 'Std.Ret', 'Sharpe.Ratio', 'Tot.PnL', 'Win.Ratio']
    backtest_rs = pd.DataFrame(index = p.index, columns=cols)
    #   Create MACD
    macd = tech.MACD(p=p, windows=windows, signal_type=signal_type)
    #   Chnage data type
    p = p.astype('float')
    #   Edit backtest dataframe
    backtest_rs['Num.Obs.'] = np.sum(~np.isnan(p),axis=1)
    backtest_rs['Num.Trade'] = cntTrades(signal=macd[4])
    backtest_rs['Tot.Ret'] = calTotRtn(p=p, signal=macd[4])
    backtest_rs['Std.Ret'] = calStdRtn(p=p, signal=macd[4])
    backtest_rs['Sharpe.Ratio'] = sharpeRatio(p=p, signal=macd[4])
    backtest_rs['Tot.PnL'] = PnL(p=p, signal=macd[4])
    backtest_rs['Win.Ratio'] = winRatio(p=p, signal=macd[4])
    return backtest_rs
