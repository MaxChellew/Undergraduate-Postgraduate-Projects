############################# Title #############################

''' Datatesting for the MACD indicator '''

############################ Settings ###########################

''' Install Libarys '''
import pandas as pd
import os as os
import numpy as np

''' Setting Work-directory '''
os.chdir(os.path.dirname(os.path.realpath(__file__)))

''' Import functions '''
import preanalysis_functions as pre
import matplotlib.pyplot as plt

########################## Prepare Data #########################

''' Create price matrix with size (time x day) '''
#   TESLA
v_matrix_TSLA = pre.transformVol(x = pd.read_csv("TSLA_5m.csv",
                                              index_col='Datetime',
                                              parse_dates=['Datetime']),
                                              freq = "5T", 
                                              usecol = "Close")
#   NVIDA
v_matrix_NVDA = pre.transformVol(x = pd.read_csv("NVDA_5m.csv",
                                              index_col='Datetime', 
                                              parse_dates=['Datetime']),
                                              freq = "5T", 
                                              usecol = "Close")
#   ALPHABET
v_matrix_GOOG = pre.transformVol(x = pd.read_csv("GOOG_5m.csv",
                                              index_col='Datetime',
                                              parse_dates=['Datetime']),
                                              freq = "5T", 
                                              usecol = "Close")

##################### Save Volume data ######################

''' Download to CSV file '''
v_matrix_TSLA.to_csv('TSLA_volume.csv')
v_matrix_NVDA.to_csv("NVDA_volume.csv")
v_matrix_GOOG.to_csv("GOOG_volume.csv")

################## Average Volume function ##################

''' Average volume function '''
def avgVolume(v): # insert volume matrix
    time_index = pd.date_range(start=pd.to_datetime('14:30:00', format="%H:%M:%S"), end=pd.to_datetime('20:55:00', format="%H:%M:%S"), freq='5T')
    avgV = pd.DataFrame(index=[0],columns=time_index.time)
    for i in list(range(0, len(v.values[0,:]))):
        avgV.loc[0,time_index.time[i]] = np.average(v.values[:,i])
    return avgV

####################### Volume Smile ########################

''' Volume data '''
#   TESLA
v_TSLA = avgVolume(v=v_matrix_TSLA)
#   NVIDA
v_NVDA = avgVolume(v=v_matrix_NVDA)
#   ALPHABET
v_GOOG = avgVolume(v=v_matrix_GOOG)


''' Volume smile plots '''
#   TESLA
plt.plot(v_TSLA.values.transpose(), color="Blue")
#   NVIDA
plt.plot(v_NVDA.values.transpose(), color="Green")
#   ALPHABET
plt.plot(v_GOOG.values.transpose(), color="Red")
#   Graph labels
plt.title("Volume Smile")
plt.ylabel("Average Trading Volume")
plt.xlabel("Time periods (5m intervals)")
plt.legend(["TSLA", "NVIDA", "GOOG"])
plt.savefig('volume_smile', dpi=300)
