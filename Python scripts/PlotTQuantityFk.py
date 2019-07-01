import matplotlib.pyplot as plt
import numpy as np
import math
import Input as input
import Path as path
import os

def PlotIsingResults(isingResultsFilePath):
    ts, Es = input.ReadTQuantityFk(isingResultsFilePath)

    # ts = ts[:25000]
    # Es = Es[:25000]
    # Ms = Ms[:25000]

    plt.plot(ts, Es)
    # plt.xlabel('t')
    # plt.ylabel('E')
    # plt.title("E(t) T=2.269 L=32")
    plt.show()


PlotIsingResults(os.path.join(path.TQuantitiesDirPath, "Cv.dat"))