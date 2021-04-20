#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib import style
import pandas as pd


# In[ ]:


# plt.style.use('fivethirtyeight')
plt.style.use('seaborn')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)


# In[ ]:


def animation(i):
    EEGDATAFRAME = pd.read_csv('eegdata.csv')
    x = []
    y = []
    
    x = EEGDATAFRAME[0:i]['Time']
    y = EEGDATAFRAME[0:i]['Attention']
    
    ax.clear()
    ax.plot(x, y)


# In[ ]:


animation = FuncAnimation(fig, func=animation, interval=1000)
plt.show()


# In[ ]:




