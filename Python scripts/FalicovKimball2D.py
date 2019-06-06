import math
import random
import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt

t = 1
L = 20
N = L*L

dE = 0.5
gamma = 0.1
mu = 0
U = 8
samplesAmount = 50

def FillHamiltonianMatrix():
    matrixH = np.matrix(np.zeros([N, N], dtype=float))
    for i in range(L):
        for j in range(L):
            jLeft = j-1
            jRight = j+1
            iUp = i-1
            iDown = i+1

            #Apply periodic boundary conditions
            if jLeft < 0:
                jLeft = L-1
            if jRight >= L:
                jRight = 0
            if iUp < 0:
                iUp = L-1
            if iDown >= L:
                iDown = 0

            ijNodeNr = i*L + j
            leftNodeNr = i*L + jLeft
            rightNodeNr = i*L + jRight
            upNodeNr = iUp*L + j
            downNodeNr = iDown*L + j

            matrixH[(ijNodeNr, leftNodeNr)] = t
            matrixH[(ijNodeNr, rightNodeNr)] = t
            matrixH[(ijNodeNr, upNodeNr)] = t
            matrixH[(ijNodeNr, downNodeNr)] = t
    return matrixH

def ApplyFalKimInteractions(matrixH):
    for i in range(N):
        randomNr = random.randint(0, 1)
        if randomNr == 1:
            matrixH[(i, i)] += U

def CalculateEnergies():
    matrixH = FillHamiltonianMatrix()
    ApplyFalKimInteractions(matrixH)
    eigVals, eigVecs = la.eig(matrixH)
    eigVals.sort()
    return eigVals

def Lorentzian(x, x0):
    lorentzian = 1 / (math.pi*gamma * (1 + ( (x-x0)/gamma )**2 ))
    return lorentzian

def CalculateDensityOfStates(energies):
    minE = -4 * t - 0.5
    maxE = 4 * t + 9.5
    Es = []
    densityOfStates = []
    E = minE
    while E <= maxE:
        densityOfStateSum = 0.0
        for energy in energies:
            densityOfStateSum += Lorentzian(energy, E) 
        Es.append(E)
        densityOfStates.append(densityOfStateSum)
        E += dE
    return Es, densityOfStates

def CalculateAverageDensityOfStates():
    aveDensityOfStates = []
    Es = {}
    for i in range(samplesAmount):
        energies = CalculateEnergies()
        Es, densityOfStates = CalculateDensityOfStates(energies)
        if i == 0:
            aveDensityOfStates = [0.0] * len(densityOfStates)
        for j in range(len(densityOfStates)):
            aveDensityOfStates[j] += densityOfStates[j]
    for k in range(len(aveDensityOfStates)):
        aveDensityOfStates[k] = aveDensityOfStates[k] / samplesAmount
    return Es, aveDensityOfStates

def f():
    # energies = CalculateEnergies()
    # Xs = np.arange(1, N + 1, 1)
    # plt.plot(Xs, energies)
    # plt.show()
    Es, aveDensityOfStates = CalculateAverageDensityOfStates()
    plt.plot(Es, aveDensityOfStates)
    plt.show()

f()