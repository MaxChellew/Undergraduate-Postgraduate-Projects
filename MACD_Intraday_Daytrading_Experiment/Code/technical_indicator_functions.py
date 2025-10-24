############################# Title #############################

''' Technical Indicator Functions '''

############################ Settings ###########################

''' Import Libarys '''
import pandas as pd
import numpy as np

################# Technical Indicator functions #################

''' Simple moving average (SMA) technical indicator Function'''  
def SMA(p,          # Insert Price Matrix
        window):    # Insert Look-back window
    #   Create dataframe
    sma = pd.DataFrame(index=p.index, columns=p.columns)
    #   Insert simple moving average into dataframe
    for i in window+np.arange(p.shape[1]-window):
        #   loop each column for all dates
        sma.iloc[:,i] = np.mean(p.iloc[:,(i-window):(i-1)],axis=1)
    return sma

''' Exponential moving average (EMA) technical indicator Function '''
def EMA(p,          # Insert Price matrix
        window):    # Insert Look-back window
    #   Create dataframe
    ema = pd.DataFrame(index=p.index, columns=p.columns)
    #   Find SMA
    sma = SMA(p=p, window=window)
    #   Find Alpha 
    alpha = 2/(window+1)
    #   Insert Exponential moving average into dataframe
    for i in window+np.arange(p.shape[1]-window):
        #  loop each column for all dates 
        if i==(window+np.arange(p.shape[1]-window))[0]:
            ema.iloc[:,i] = sma.iloc[:,i]
        else:
            ema.iloc[:,i] = alpha*(p.iloc[:,i]-ema.iloc[:,i-1]) + ema.iloc[:,i-1]
    return ema

''' Moving average convergence divergence (MACD) technical indicator + EMA + signial Function'''
def MACD(p,             # Insert Price Matrix
         windows,       # Insert Look-back windows (short_term window, long_term window, Signal window)
         signal_type):  # Insert signal ("Long", "Short", "Both")
    #   Create dataframe
    signals = pd.DataFrame(index=p.index,columns=p.columns)
    #   Short term EMA
    short_term_ema = EMA(p=p, window=windows[0])
    #   Long term EMA
    long_term_ema = EMA(p=p, window=windows[1])
    #   MACD
    macd = short_term_ema - long_term_ema
    #   Signal MACD
    signal_macd = pd.DataFrame(index=p.index, columns=p.columns)
    sma = SMA(p=macd, window=windows[2])
    alpha = 2/(windows[2]+1)
    for i in windows[2]+np.arange(p.shape[1]-windows[2]):
        #  loop each column for all dates 
        if i==(windows[2]+windows[1]+np.arange(p.shape[1]-windows[2]))[0]:
            signal_macd.iloc[:,i] = sma.iloc[:,i]
        else:
            signal_macd.iloc[:,i] = alpha*(macd.iloc[:,i]-signal_macd.iloc[:,i-1]) + signal_macd.iloc[:,i-1]
    #   Create buy and sell singals 
    if signal_type == "Long":
        #   Long singals
        signals = (macd>signal_macd)*(1)
    if signal_type == "Short":
        #   Short signals
        signals = (macd<signal_macd)*(-1)
    if signal_type == "Both":
        #   Both long and short signals
        signals = (macd>signal_macd)*1+(macd<signal_macd)*(-1)
    #   shifting indexing to refelect using information up till i-1 to make a decision for i
    signals = signals.shift(periods=1, axis="columns")
    signals.iloc[:,1]=0
    #   Close position at end of the day
    signals.iloc[:,-1]=0
    #   Return MACD, MACD signal, 
    return macd, signal_macd, short_term_ema, long_term_ema, signals