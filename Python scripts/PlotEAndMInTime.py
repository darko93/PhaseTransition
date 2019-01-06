import matplotlib.pyplot as plt
import numpy as np
import math
import Input as input
import Path as path
import os

def PlotIsingResults(isingResultsFilePath):
    ts, Es, Ms = input.ReadtsAndEsAndMs(isingResultsFilePath)

    plt.plot(ts, Es)
    plt.xlabel('t')
    plt.ylabel('E')
    plt.show()

    plt.plot(ts, Ms)
    plt.xlabel('t')
    plt.ylabel('M')
    plt.show()


PlotIsingResults(os.path.join(path.quantitiesDirPath, "Quantities_L=32_T=3.000_h=0.000.dat"))