import numpy as np
import numpy.linalg as la
import math
import random
from FkSimulationParameters import FkSimulationParameters

class FalicovKimballModel:

    def GetFilledHamiltonianMatrix(self, simParams):
        matrixH = np.matrix(np.zeros([simParams.N, simParams.N], dtype=float))
        L = simParams.L
        t = simParams.t
        for i in range(simParams.L):
            for j in range(simParams.L):
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

    def ApplyFalKimInteractions(self, simParams, matrixH):
        for i in range(simParams.N):
            randomNr = random.randint(0, 1)
            if randomNr == 1:
                matrixH[(i, i)] += simParams.U

    def CalculateEnergies(self, simParams):
        matrixH = self.GetFilledHamiltonianMatrix(simParams)
        self.ApplyFalKimInteractions(simParams, matrixH)
        eigVals, eigVecs = la.eig(matrixH)
        eigVals.sort()
        return eigVals

    def Lorentzian(self, gamma, x, x0):
        lorentzian = 1 / (math.pi*gamma * (1 + ( (x-x0)/gamma )**2 ))
        return lorentzian

    def CalculateDensityOfStates(self, simParams, energies):
        minE = -4 * simParams.t - 0.5
        maxE = 4 * simParams.t + 9.5
        Es = []
        densityOfStates = []
        E = minE
        while E <= maxE:
            densityOfStateSum = 0.0
            for energy in energies:
                densityOfStateSum += self.Lorentzian(simParams.gamma, energy, E) 
            Es.append(E)
            densityOfStates.append(densityOfStateSum)
            E += simParams.dE
        return Es, densityOfStates

    def CalculateAverageDensityOfStates(self, simParams):
        aveDensityOfStates = []
        Es = {}
        for i in range(simParams.mcsAmount):
            energies = self.CalculateEnergies(simParams)
            Es, densityOfStates = self.CalculateDensityOfStates(simParams, energies)
            if i == 0:
                aveDensityOfStates = [0.0] * len(densityOfStates)
            for j in range(len(densityOfStates)):
                aveDensityOfStates[j] += densityOfStates[j]
        for k in range(len(aveDensityOfStates)):
            aveDensityOfStates[k] /= simParams.mcsAmount
        return Es, aveDensityOfStates