import matplotlib.pyplot as plt
import numpy as np
import math
import Input as input
import Path as path
import os

def PlotIsingResults(isingResultsFilePath):
    ts, Es, Ms = input.ReadtsAndEsAndMs(isingResultsFilePath)

    ts = ts[:25000]
    Es = Es[:25000]
    Ms = Ms[:25000]

    plt.plot(ts, Es)
    plt.xlabel('t')
    plt.ylabel('E')
    plt.title("E(t) T=2.269 L=32")
    plt.show()

    plt.plot(ts, Ms)
    plt.xlabel('t')
    plt.ylabel('M')
    plt.title("M(t) T=2.269 L=32")
    plt.show()


PlotIsingResults(os.path.join(path.quantitiesDirPath, "Quantities_L=32_T=2.269_h=0.000.dat"))