#!/usr/bin/env python
# coding: utf-8

# In[1]:


# Importing libraries
import json
import time
from telnetlib import Telnet
import serial
import pandas as pd

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import warnings
warnings.filterwarnings('ignore')


# In[2]:


# Initializing keys, PORT and telnet configuration

ser = serial.Serial('COM4', 9600, timeout=1);
tn=Telnet('localhost',13854);

start=time.clock();

i=0;
tn.write(b'{"enableRawOutput": true, "format": "Json"}');

eSenseDict={'attention':0, 'meditation':0};
waveDict={'lowGamma':0, 'highGamma':0, 'highAlpha':0, 'delta':0, 'highBeta':0, 'lowAlpha':0, 'lowBeta':0, 'theta':0};
signalLevel=0;


# In[3]:


EEGDATAFRAME = pd.DataFrame(columns=['Time', 'Attention', 'Meditation','Blink_Strength'])


while i<100:
    eeg_data = []

    blinkStrength=0;

    line=tn.read_until(b'\r');
#     print(line);

    if len(line) > 20:
        timediff=time.clock()-start;
        dict=json.loads((line));
        if "poorSignalLevel" in dict:
            signalLevel=dict['poorSignalLevel'];
        if "blinkStrength" in dict:
            blinkStrength=dict['blinkStrength'];
        if "eegPower" in dict:
            waveDict=dict['eegPower'];
            eSenseDict=dict['eSense'];

        attentionStr=str(eSenseDict['attention']);
        meditationStr=str(eSenseDict['meditation']);
        blinkStrengthStr=str(blinkStrength);
        seconds = time.time();

        eeg_data.append({'Time': seconds,'Attention': attentionStr, 'Meditation': meditationStr, 'Blink_Strength':blinkStrengthStr})
        print(eeg_data);
        eeg_df = pd.DataFrame(eeg_data)
        EEGDATAFRAME = EEGDATAFRAME.append(eeg_df, ignore_index=True)
#         print(EEGDATAFRAME) 
        EEGDATAFRAME.to_csv('eegdata.csv',index=True)

#         print("Attention: " + attentionStr);
#         print("Meditation: " + meditationStr);
#         print("Blink Strength: " + blinkStrengthStr);
#         print("");

        attentionInt = int(attentionStr)
        if attentionInt > 70:
            ser.write(str.encode('a'));
            time.sleep(1)

        meditationInt = int(meditationStr)
        if meditationInt > 70:
            ser.write(str.encode('b'));
            time.sleep(1)

        blinkStrengthInt = int(blinkStrengthStr)
        if blinkStrengthInt > 1:
            ser.write(str.encode('c'));
            time.sleep(1)

ser.close();
tn.close();


# In[ ]:




