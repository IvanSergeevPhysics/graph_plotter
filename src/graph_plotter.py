#!/usr/bin/env python
# coding: utf-8

import pandas as pd
import matplotlib.pyplot as plt

def getData(path):
    df = pd.read_csv(path, sep=" ", names=["x", "y"])
    return list(df.x), list(df.y)

def plotGraph(x, y):
    plt.plot(x, y)
    plt.grid()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.savefig(fname = 'result.png', format = 'png')
    plt.show()
    
def result():
    x, y = getData("nodes.txt")
    plotGraph(x, y)
    
result()

