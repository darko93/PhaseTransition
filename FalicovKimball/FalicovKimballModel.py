import numpy as np
import numpy.linalg as la
import math
import random
from FkSimulationParameters import FkSimulationParameters
from FkMeantimeQuantities import FkMeantimeQuantities

class FalicovKimballModel:

    simParams = None
    filledMatrixH = None
    occupiedSites = None
    emptySites = None
    ions = None
    prevFreeEn = 0.0
    Es = None
    output = None


    def __init__(self, output):
        self.output = output


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


    def getFilledHamiltonianMatrix(self):

        if self.filledMatrixH is not None:
            return self.filledMatrixH

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

        self.filledMatrixH = matrixH
        return matrixH


    def applyFalKimInteractions(self, matrixH):
        for i in range(self.simParams.N):
            if self.ions[i] == 1:
                matrixH[(i, i)] += self.simParams.U


    def energies(self):
        matrixH = self.getFilledHamiltonianMatrix()
        self.applyFalKimInteractions(matrixH)
        eigVals, eigVecs = la.eig(self.filledMatrixH)
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
            densityOfStatePerSite = densityOfStateSum * NFactor
            densityOfStates.append(densityOfStatePerSite)
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
        occupiedSitesAmount = int(self.simParams.elConc * N)
        occupiedSites = random.sample(possibleIndices, k=occupiedSitesAmount)
        emptySites = list()
        for siteIndex in possibleIndices:
            if not siteIndex in occupiedSites:
                emptySites.append(siteIndex)
        
        ions = [0] * N
        for occupiedSite in occupiedSites:
            ions[occupiedSite] = 1

        self.occupiedSites = occupiedSites
        self.emptySites = emptySites
        self.ions = ions


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


    def correlationFunction(self, n=1):
        L = self.simParams.L
        ions = self.ions
        correl = 0.0
        for i in range(L):
            for j in range(L):
                ijSiteNr, leftSiteNr, rightSiteNr, upSiteNr, downSiteNr = self.getNeigboringSitesNrs(i, j)
                correl = ions[ijSiteNr] * (ions[leftSiteNr] + ions[rightSiteNr] + ions[upSiteNr] + ions[downSiteNr])
        correl *= 4 * self.simParams.NFactor
        return correl


    def metropolisStep(self):
        freeEn1 = 0.0
        if self.Es is None: # If this is totally first Metropolis step in the simulation
            self.Es = self.energies()
            freeEn1 = self.freeEnergy(self.Es)
        else:
            freeEn1 = self.prevFreeEn
        # Do a trial ionic configuration change
        sourceSite = random.choice(self.occupiedSites)
        destSite = random.choice(self.emptySites)
        self.occupiedSites.remove(sourceSite)
        self.occupiedSites.append(destSite)
        self.emptySites.remove(destSite)
        self.emptySites.append(sourceSite)
        self.ions[sourceSite] = 0
        self.ions[destSite] = 1
        self.filledMatrixH[(sourceSite, sourceSite)] = 0
        self.filledMatrixH[(destSite, destSite)] = 1
        prevEs = self.Es
        self.Es = self.energies()
        freeEn2 = self.freeEnergy(self.Es)
        self.prevFreeEn = freeEn2
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
                self.ions[sourceSite] = 1
                self.ions[destSite] = 0
                self.filledMatrixH[(sourceSite, sourceSite)] = 1
                self.filledMatrixH[(destSite, destSite)] = 0
                self.Es = prevEs
                self.prevFreeEn = freeEn1


    def initialize(self, simParams, initIons = None):
        self.simParams = simParams
        if initIons is None:
            self.chooseIonicConfiguration()
        else:
            self.ions = initIons


    def fullSimulationAfterInitialization(self):
        simParams = self.simParams
        if simParams.saveMeantimeQuantities and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.metropolisStep()
                
                groundStateE = min(self.Es)
                g1 = self.correlationFunction(n=1)
                quantities = FkMeantimeQuantities(groundStateE, g1)
                self.output.saveMeantimQuantities(quantities, simParams, mcs)

                if mcs % simParams.savingIonsMcsInterval == 0:
                    self.output.saveIons(self)

        elif simParams.saveMeantimQuantities and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.metropolisStep()
                
                groundStateE = min(self.Es)
                g1 = self.correlationFunction(n=1)
                quantities = FkMeantimeQuantities(groundStateE, g1)
                self.output.saveMeantimQuantities(quantities, simParams, mcs)

        elif not simParams.saveMeantimQuantities and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.metropolisStep()

                if mcs % simParams.savingIonsMcsInterval == 0:
                    self.output.saveIons(self)

        elif not simParams.saveMeantimQuantities and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.metropolisStep()


    def fullSimulation(self, simParams, initIons = None):
        self.initialize(simParams, initIons)
        self.fullSimulationAfterInitialization()