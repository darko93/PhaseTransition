import os
import matplotlib.pyplot as plt
import numpy as np
import Path as path
import Input as input


def PlotIons(ionsFileName):
    L = 20
    ionsFilePath = os.path.join(path.IonsDirPath, ionsFileName)
    ionsConfigs = input.ReadIons(ionsFilePath)
    ionsConfig = ionsConfigs[100]
    # ionsConfig = ionsConfigs[len(ionsConfigs) - 1]
    ionsConfig = np.reshape(ionsConfig, (-1, L))

    plt.xticks([])
    plt.yticks([])
    plt.imshow(ionsConfig, cmap='Greys',  interpolation='nearest')
    plt.show()

def PlotAllIons():
    ionsFileNames = ["Ions_L=20_U=1.000_T=0.055.dat"]
    # ionsFileNames = ["Ions_L=20_U=8.000_T=0.100.dat", "Ions_L=20_U=8.000_T=1.000.dat"]
    # ionsFileNames = ["Ions_L=20_U=1.000_T=0.020.dat", "Ions_L=20_U=1.000_T=0.050.dat", "Ions_L=20_U=1.000_T=0.100.dat"]
    for ionsFileName in ionsFileNames:
        PlotIons(ionsFileName)

def PlotSpins(spinsFileName):
    spinsFilePath = os.path.join(path.spinsDirPath, spinsFileName)
    L, T, spinsConfigs = input.ReadSpins(spinsFilePath)
    spinsConfig = spinsConfigs[len(spinsConfigs) - 1]
    spinsConfig = np.reshape(spinsConfig, (-1, L))

    plt.xticks([])
    plt.yticks([])
    plt.imshow(spinsConfig, cmap='Greys',  interpolation='nearest')
    plt.show()

    # G is a NxNx3 matrix
    G = np.zeros((L,L,3))

    # Where we set the RGB for each pixel
    # G[ionsConfig < 0.5] = [1,1,1]
    # G[ionsConfig > 0.5] = [0,0,0]
    G[spinsConfig < 0.5] = [0,0,1]
    G[spinsConfig > 0.5] = [1,0,0]

    plt.xticks([])
    plt.yticks([])
    plt.imshow(G,interpolation='nearest')
    plt.show()    


def PlotAllSpins():
    spinsFileNames = ["Spins_J=1_L=50_T=1.000_h=0.000.dat", "Spins_J=1_L=50_T=2.300_h=0.000.dat", "Spins_J=1_L=50_T=3.500_h=0.000.dat"]
    for spinsFileName in spinsFileNames:
        PlotSpins(spinsFileName)


PlotAllIons()