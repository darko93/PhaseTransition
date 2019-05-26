import math
import random
import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt

N = 100
t = 1
dE = 0.1
gamma = dE
mu = 0
U = 0.5
samplesAmount = 1000

def CalculateEnergies():
    matrixH = t * np.matrix(np.eye(N, k=1), dtype=float) + t * np.matrix(np.eye(N, k=-1), dtype=float) - mu * np.matrix(np.eye(N), dtype=float)
    ApplyPeriodicBoundaryConditions(matrixH)
    ApplyFalKimInteractions(matrixH)
    eigVals, eigVecs = la.eig(matrixH)
    eigVals.sort()
    return eigVals

def ApplyPeriodicBoundaryConditions(matrixH):
    matrixH[(0, N-1)] = t
    matrixH[(N-1, 0)] = t

def ApplyFalKimInteractions(matrixH):
    for i in range(N):
        randomNr = random.randint(0, 1)
        if randomNr == 1:
            matrixH[(i, i)] += U

def Lorentzian(x, x0):
    lorentzian = 1 / (math.pi*gamma * (1 + ( (x-x0)/gamma )**2 ))
    return lorentzian

def CalculateDensityOfStates(energies):
    minE = -2 * t - 0.25
    maxE = 2 * t + 1
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

Es, aveDensityOfStates = CalculateAverageDensityOfStates()
plt.plot(Es, aveDensityOfStates)
plt.show()

# energies = CalculateEnergies()
# Xs = np.arange(1, N + 1, 1)
# plt.plot(Xs, energies)
# plt.show()
# Es, densityOfStates = CalculateDensityOfStates(energies)
# plt.plot(Es, densityOfStates)
# plt.show()