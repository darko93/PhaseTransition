import os
import matplotlib.pyplot as plt
import Input as input
import Path as path

def ReadAutocorrelsDic():
    autocorrelDirPath = path.autocorrelDirPath
    autocorrelsDic = dict()
    for autocorrelFileName in os.listdir(autocorrelDirPath):
        autocorrelFilePath = os.path.join(autocorrelDirPath, autocorrelFileName)
        L, ts, EAutocorrels, MAutocorrels = input.ReadAutocorrelations(autocorrelFilePath)
        autocorrelsDic[L] = (ts, EAutocorrels, MAutocorrels)
    return autocorrelsDic  

def PlotAutocorrelations(autocorrelsDic, quantityIndex):
    autocorrelsDic = ReadAutocorrelsDic()
    plt.semilogy(autocorrelsDic[4][0], autocorrelsDic[4][quantityIndex], "g-x",\
        autocorrelsDic[8][0], autocorrelsDic[8][quantityIndex], "c-^",\
        autocorrelsDic[16][0], autocorrelsDic[16][quantityIndex], "b-o",\
        autocorrelsDic[32][0], autocorrelsDic[32][quantityIndex], "m-d")
    plt.xlabel('t')
    plt.ylabel('phi(t)')
    plt.show()

def PlotBothAutocorrelations():
    autocorrelsDic = ReadAutocorrelsDic()
    energyIndex = 1
    magnetizationIndex = 2
    PlotAutocorrelations(autocorrelsDic, energyIndex)
    PlotAutocorrelations(autocorrelsDic, magnetizationIndex)

PlotBothAutocorrelations()
