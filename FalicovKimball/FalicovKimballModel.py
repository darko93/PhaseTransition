import numpy as np
import numpy.linalg as la
import math
import random
from FkSimulationParameters import FkSimulationParameters

class FalicovKimballModel:

    mcs = 1
    simParams = None
    matrixH = None
    occupiedSites = None
    emptySites = None
    ionicConfig = None
    lastFreeEn = 0.0

    def getNeigboringSitesNrs(self, i, j):
        L = self.simParams.L

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

        ijSiteNr = i*L + j
        leftSiteNr = i*L + jLeft
        rightSiteNr = i*L + jRight
        upSitesNr = iUp*L + j
        downSitesNr = iDown*L + j

        return ijSiteNr, leftSiteNr, rightSiteNr, upSitesNr, downSitesNr

    def fillHamiltonianMatrix(self):

        if self.mcs > 1:
            return

        matrixH = np.matrix(np.zeros([self.simParams.N, self.simParams.N], dtype=float))
        L = self.simParams.L
        t = self.simParams.t
        for i in range(L):
            for j in range(L):
                ijSiteNr, leftSiteNr, rightSiteNr, upSiteNr, downSiteNr = self.getNeigboringSitesNrs(i, j)

                matrixH[(ijSiteNr, leftSiteNr)] = t
                matrixH[(ijSiteNr, rightSiteNr)] = t
                matrixH[(ijSiteNr, upSiteNr)] = t
                matrixH[(ijSiteNr, downSiteNr)] = t

                self.applyFalKimInteractions(matrixH)
        self.matrixH = matrixH

    def applyFalKimInteractions(self, matrixH):
        for i in range(self.simParams.N):
            if self.ionicConfig[i] == 1:
                matrixH[(i, i)] += self.simParams.U

    def energies(self):
        self.fillHamiltonianMatrix()
        eigVals, eigVecs = la.eig(self.matrixH)
        return eigVals

    def lorentzian(self, x, x0):
        gamma = self.simParams.gamma
        lorentzian = 1 / (math.pi*gamma * (1 + ( (x-x0)/gamma )**2 ))
        return lorentzian

    def densityOfStates(self, energies):
        t = self.simParams.t
        dE = self.simParams.dE
        NFactor = self.simParams.NFactor
        minE = -4 * t - 0.5
        maxE = 4 * t + 9.5
        Es = []
        densityOfStates = []
        E = minE
        while E <= maxE:
            densityOfStateSum = 0.0
            for energy in energies:
                densityOfStateSum += self.lorentzian(energy, E) 
            Es.append(E)
            #densityOfStatePerSite = densityOfStateSum * NFactor
            densityOfStates.append(densityOfStateSum)
            E += dE
        return Es, densityOfStates

    def averageDensityOfStates(self):
        mcsAmount = self.simParams.mcsAmount
        aveDensityOfStates = []
        Es = {}
        for i in range(mcsAmount):
            energies = self.energies()
            Es, densityOfStates = self.densityOfStates(energies)
            if i == 0:
                aveDensityOfStates = [0.0] * len(densityOfStates)
            for j in range(len(Es)):
                aveDensityOfStates[j] += densityOfStates[j]
        for k in range(len(Es)):
            aveDensityOfStates[k] /= mcsAmount
        return Es, aveDensityOfStates



    def chooseIonicConfiguration(self):
        N = self.simParams.N
        possibleIndices = list()
        for i in range(N):
            possibleIndices.append(i)
        halfN = int(0.5 * N)
        occupiedSites = random.sample(possibleIndices, k=halfN)
        emptySites = list()
        for siteIndex in possibleIndices:
            if not siteIndex in occupiedSites:
                emptySites.append(siteIndex)
        
        ionicConfig = [0] * N
        for occupiedSite in occupiedSites:
            ionicConfig[occupiedSite] = 1

        self.occupiedSites = occupiedSites
        self.emptySites = emptySites
        self.ionicConfig = ionicConfig

    def freeEnergy(self, energies):
        simParams = self.simParams

        # version optimized, but probably not really accurate - taking logarithm of product instead of sum of logarithm
        # product = 1.0
        # for energy in energies:
        #     product *= (1 + math.exp(-simParams.beta * (energy - simParams.mu)))
        # freeEnergy = -simParams.kB * simParams.T * math.log(product)

        sum = 0.0
        for energy in energies:
            sum += math.log(1 + math.exp(-simParams.beta * (energy - simParams.mu)))
        freeEnergy = -simParams.kB * simParams.T * sum

        return freeEnergy

    def metropolisStep(self):
        freeEn1 = 0.0
        if self.mcs == 1:
            energies = self.energies()
            freeEn1 = self.freeEnergy(energies)
        else:
            freeEn1 = self.lastFreeEn
        # Do a trial ionic configuration change
        sourceSite = random.choice(self.occupiedSites)
        destSite = random.choice(self.emptySites)
        self.occupiedSites.remove(sourceSite)
        self.occupiedSites.append(destSite)
        self.emptySites.remove(destSite)
        self.emptySites.append(sourceSite)
        self.ionicConfig[sourceSite] = 0
        self.ionicConfig[destSite] = 1
        self.matrixH[(sourceSite, sourceSite)] = 0
        self.matrixH[(destSite, destSite)] = 1
        energies = self.energies()
        freeEn2 = self.freeEnergy(energies)
        self.lastFreeEn = freeEn2
        if freeEn2 > freeEn1:
            deltaFreeEn = freeEn2 - freeEn1
            boltzmanFactor = math.exp(-self.simParams.beta * deltaFreeEn)
            randomNr = random.random()
            if randomNr > boltzmanFactor:
                # Revert ionic configuration change, when deltaF > 0 <=> F2 > F1 and random > boltzmanFactor
                self.occupiedSites.remove(destSite)
                self.occupiedSites.append(sourceSite)
                self.emptySites.remove(sourceSite)
                self.emptySites.append(destSite)
                self.ionicConfig[sourceSite] = 1
                self.ionicConfig[destSite] = 0
                self.matrixH[(sourceSite, sourceSite)] = 1
                self.matrixH[(destSite, destSite)] = 0
                self.lastFreeEn = freeEn1

    def initialize(self, simParams, initIonicConfig = None):
        self.simParams = simParams
        if initIonicConfig is None:
            self.chooseIonicConfiguration()
        else:
            self.ionicConfig = initIonicConfig

    def correlationFunction(self, n=1):
        L = self.simParams.L
        ionicConfig = self.ionicConfig
        correl = 0.0
        for i in range(L):
            for j in range(L):
                ijSiteNr, leftSiteNr, rightSiteNr, upSiteNr, downSiteNr = self.getNeigboringSitesNrs(i, j)
                correl = ionicConfig[ijSiteNr] * (ionicConfig[leftSiteNr] + ionicConfig[rightSiteNr] + ionicConfig[upSiteNr] + ionicConfig[downSiteNr])
        correl *= 4 * self.simParams.NFactor
        return correl


    def fullSimulation(self, simParams, initIonicConfig = None):
        self.initialize(simParams, initIonicConfig)
        if simParams.saveMeantimeQuantities and simParams.saveIonicConfig:
            for self.mcs in range(1, simParams.mcsAmount + 1):
                self.metropolisStep()
                # #save meantime quantities
                # if self.mcs % simParams.savingIonicConfigMcsInterval == 0:
                #     #save ionic config