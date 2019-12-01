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
    # plt.semilogy(autocorrelsDic[4][0], autocorrelsDic[4][quantityIndex], "g-x",\
    #     autocorrelsDic[8][0], autocorrelsDic[8][quantityIndex], "c-^",\
    #     autocorrelsDic[16][0], autocorrelsDic[16][quantityIndex], "b-o",\
    #     autocorrelsDic[32][0], autocorrelsDic[32][quantityIndex], "m-d")
    plt.semilogy(autocorrelsDic[4][0], autocorrelsDic[4][quantityIndex], "g-x", label="L=4")
    plt.semilogy(autocorrelsDic[8][0], autocorrelsDic[8][quantityIndex], "c-^", label="L=8")
    plt.semilogy(autocorrelsDic[16][0], autocorrelsDic[16][quantityIndex], "b-o", label="L=16")
    plt.semilogy(autocorrelsDic[32][0], autocorrelsDic[32][quantityIndex], "m-d", label="L=32")
    # plt.legend(loc='center right')
    plt.legend(loc='top right')
    plt.xlabel('t')
    ylabel = ""
    # if quantityIndex == 1:
    #     ylabel = 'autocorrelation function of energy for T=2.269'
    # elif quantityIndex == 2:
    #     ylabel = 'autocorrelation function of magnetization for T=2.269'
    plt.ylabel(ylabel)
    plt.show()

def PlotBothAutocorrelations():
    autocorrelsDic = ReadAutocorrelsDic()
    energyIndex = 1
    magnetizationIndex = 2
    PlotAutocorrelations(autocorrelsDic, energyIndex)
    PlotAutocorrelations(autocorrelsDic, magnetizationIndex)

PlotBothAutocorrelations()
