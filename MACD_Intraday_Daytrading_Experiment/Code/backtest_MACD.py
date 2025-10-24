############################# Title #############################

''' Backtest of the MACD indicator '''

############################ Settings ###########################

''' Install Libarys '''
import pandas as pd
import os as os

''' Setting Work-directory '''
os.chdir(os.path.dirname(os.path.realpath(__file__)))

''' Import functions '''
import preanalysis_functions as pre
import backtest_functions as bt

########################## Prepare Data #########################

''' Create price matrix with size (time x day) '''
#   TESLA
p_matrix_TSLA = pre.transform(x = pd.read_csv("TSLA_5m.csv",
                                              index_col='Datetime',
                                              parse_dates=['Datetime']),
                                              freq = "5T", 
                                              usecol = "Close")
#   NIVIDA
p_matrix_NVDA = pre.transform(x = pd.read_csv("NVDA_5m.csv",
                                              index_col='Datetime', 
                                              parse_dates=['Datetime']),
                                              freq = "5T", 
                                              usecol = "Close")
#   ALPHABET
p_matrix_GOOG = pre.transform(x = pd.read_csv("GOOG_5m.csv",
                                              index_col='Datetime',
                                              parse_dates=['Datetime']),
                                              freq = "5T", 
                                              usecol = "Close")


####################### Save price data #########################

''' Download to CSV file '''
p_matrix_TSLA.to_csv('TSLA_close.csv')
p_matrix_NVDA.to_csv("NVDA_close.csv")
p_matrix_GOOG.to_csv("GOOG_close.csv")

##################### Long 6, 12, 3 tests #######################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt1 = bt.backtestMatrix(p=p_matrix_TSLA,
                             windows=[6, 12, 3],
                             signal_type="Long")
#   NIVIDA MACD
NVDA_bt1 = bt.backtestMatrix(p=p_matrix_NVDA,
                             windows=[6, 12, 3],
                             signal_type="Long")
#   ALPHABET MACD
GOOG_bt1 = bt.backtestMatrix(p=p_matrix_GOOG,
                             windows=[6, 12, 3],
                             signal_type="Long")

''' Download to CSV file '''
TSLA_bt1.to_csv('TSLA_bt1.csv')
NVDA_bt1.to_csv("NVDA_bt1.csv")
GOOG_bt1.to_csv("GOOG_bt1.csv")

##################### Short 6, 12, 3 tests ######################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt2 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[6, 12, 3],
                                signal_type="Short")
#   NIVIDA MACD
NVDA_bt2 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[6, 12, 3],
                                signal_type="Short")
#   ALPHABET MACD
GOOG_bt2 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[6, 12, 3],
                                signal_type="Short")

''' Download to CSV file '''
TSLA_bt2.to_csv("TSLA_bt2.csv")
NVDA_bt2.to_csv("NVDA_bt2.csv")
GOOG_bt2.to_csv("GOOG_bt2.csv")

##################### Long 6, 10, 4 tests ######################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt3 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[6, 10, 4],
                                signal_type="Long")
#   NIVIDA MACD
NVDA_bt3 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[6, 10, 4],
                                signal_type="Long")
#   ALPHABET MACD
GOOG_bt3 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[6, 10, 4],
                                signal_type="Long")

''' Download to CSV file '''
TSLA_bt3.to_csv("TSLA_bt3.csv")
NVDA_bt3.to_csv("NVDA_bt3.csv")
GOOG_bt3.to_csv("GOOG_bt3.csv")

##################### Short 6, 10, 4 tests #####################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt4 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[6, 10, 4],
                                signal_type="Short")
#   NIVIDA MACD
NVDA_bt4 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[6, 10, 4],
                                signal_type="Short")
#   ALPHABET MACD
GOOG_bt4 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[6, 10, 4], 
                                signal_type="Short")

''' Download to CSV file '''
TSLA_bt4.to_csv("TSLA_bt4.csv")
NVDA_bt4.to_csv("NVDA_bt4.csv")
GOOG_bt4.to_csv("GOOG_bt4.csv")

##################### Long 10, 20, 5 tests ######################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt5 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[10, 20, 5],
                                signal_type="Long")
#   NIVIDA MACD
NVDA_bt5 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[10, 20, 5],
                                signal_type="Long")
#   ALPHABET MACD
GOOG_bt5 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[10, 20, 5],
                                signal_type="Long")

''' Download to CSV file '''
TSLA_bt5.to_csv("TSLA_bt5.csv")
NVDA_bt5.to_csv("NVDA_bt5.csv")
GOOG_bt5.to_csv("GOOG_bt5.csv")

##################### Short 10, 20, 5 tests #####################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt6 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[10, 20, 5],
                                signal_type="Short")
#   NIVIDA MACD
NVDA_bt6 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[10, 20, 5],
                                signal_type="Short")
#   ALPHABET MACD
GOOG_bt6 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[10, 20, 5],
                                signal_type="Short")

''' Download to CSV file '''
TSLA_bt6.to_csv("TSLA_bt6.csv")
NVDA_bt6.to_csv("NVDA_bt6.csv")
GOOG_bt6.to_csv("GOOG_bt6.csv")

##################### Long 6, 24, 3 tests #####################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt7 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[6, 24, 3],
                                signal_type="Long")
#   NIVIDA MACD
NVDA_bt7 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[6, 24, 3],
                                signal_type="Long")
#   ALPHABET MACD
GOOG_bt7 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[6, 24, 3],
                                signal_type="Long")

''' Download to CSV file '''
TSLA_bt7.to_csv("TSLA_bt7.csv")
NVDA_bt7.to_csv("NVDA_bt7.csv")
GOOG_bt7.to_csv("GOOG_bt7.csv")

##################### Short 6, 24, 3 tests #####################

''' Compute MACD technical indicator for each stock '''
#   TESLA MACD
TSLA_bt8 = bt.backtestMatrix(p=p_matrix_TSLA,
                                windows=[6, 24, 3],
                                signal_type="Short")
#   NIVIDA MACD
NVDA_bt8 = bt.backtestMatrix(p=p_matrix_NVDA,
                                windows=[6, 24, 3],
                                signal_type="Short")
#   ALPHABET MACD
GOOG_bt8 = bt.backtestMatrix(p=p_matrix_GOOG,
                                windows=[6, 24, 3],
                                signal_type="Short")

''' Download to CSV file '''
TSLA_bt8.to_csv("TSLA_bt8.csv")
NVDA_bt8.to_csv("NVDA_bt8.csv")
GOOG_bt8.to_csv("GOOG_bt8.csv")
