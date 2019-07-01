import numpy as np
import numpy.linalg as la
import math
import random
from FkSimulationParameters import FkSimulationParameters
from FkMeantimeQuantities import FkMeantimeQuantities

class FalicovKimballModel:

    simParams = None
    matrixH = None
    occupiedSites = None
    emptySites = None
    ions = None
    prevFreeEn = 0.0
    currentEnergies = None
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

        if self.matrixH is not None:
            return self.matrixH

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
        return matrixH


    def applyFalKimInteractions(self, matrixH):
        for i in range(self.simParams.N):
            if self.ions[i] == 1:
                matrixH[(i, i)] += self.simParams.U


    def energies(self):
        matrixH = self.getFilledHamiltonianMatrix()
        eigVals, eigVecs = la.eig(matrixH)
        return eigVals


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
                correl += ions[ijSiteNr] * (ions[leftSiteNr] + ions[rightSiteNr] + ions[upSiteNr] + ions[downSiteNr])
        correl *= 4 * self.simParams.NFactor
        return correl


    def lorentzian(self, x, x0):
        gamma = self.simParams.gamma
        lorentzian = 1 / (math.pi*gamma * (1 + ( (x-x0)/gamma )**2 ))
        return lorentzian


    def densityOfStates(self, energies):
        t = self.simParams.t
        dE = self.simParams.dE
        NFactor = self.simParams.NFactor
        minE = -5 * t
        maxE = 5 * t
        Es = []
        densitiesOfStates = []
        E = minE
        while E <= maxE:
            densityOfState = 0.0
            for energy in energies:
                densityOfState += self.lorentzian(energy, E)
                # densityOfState += math.log(self.lorentzian(energy, E))
            Es.append(E)
            densityOfStatePerSite = NFactor * densityOfState
            # densityOfStatePerSite = math.exp(NFactor * densityOfState)
            densitiesOfStates.append(densityOfStatePerSite)
            E += dE
        return Es, densitiesOfStates


    def averageDensityOfStates(self):
        mcsAmount = self.simParams.mcsAmount
        aveDensityOfStates = []
        Es = {}
        for i in range(mcsAmount):
            print("mcs={0}".format(i+1), end="\r", flush=True)
            self.chooseIonicConfiguration()
            energies = self.energies()
            Es, densityOfStates = self.densityOfStates(energies)
            if i == 0:
                aveDensityOfStates = [0.0] * len(densityOfStates)
            for j in range(len(Es)):
                aveDensityOfStates[j] += densityOfStates[j]
        for k in range(len(Es)):
            aveDensityOfStates[k] /= mcsAmount
        return Es, aveDensityOfStates


    def metropolisStep(self):
        U = self.simParams.U
        freeEn1 = 0.0
        if self.currentEnergies is None: # If this is totally first Metropolis step in the simulation
            self.currentEnergies = self.energies()
            freeEn1 = self.freeEnergy(self.currentEnergies)
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
        self.matrixH[(sourceSite, sourceSite)] -= U
        self.matrixH[(destSite, destSite)] += U
        prevEnergies = self.currentEnergies
        self.currentEnergies = self.energies()
        freeEn2 = self.freeEnergy(self.currentEnergies)
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
                self.matrixH[(sourceSite, sourceSite)] += U
                self.matrixH[(destSite, destSite)] -= U
                self.currentEnergies = prevEnergies
                self.prevFreeEn = freeEn1


    def initialize(self, simParams, initIons = None):
        reuseIons = simParams.reuseIons and self.ions is not None and self.simParams is not None and self.simParams.L == simParams.L
        self.simParams = simParams
        if initIons is not None:
            self.ions = initIons
        elif not reuseIons:
            self.chooseIonicConfiguration()


    def calculateAndSaveMeantimeQuantities(self, mcs):
        groundStateE = min(self.currentEnergies)
        g1 = self.correlationFunction(n=1)
        quantities = FkMeantimeQuantities(groundStateE, g1)
        self.output.saveMeantimQuantities(quantities, self.simParams, mcs)


    def calculateAndSaveDoS(self, mcs):
        Es, densitiesOfStates = self.densityOfStates(self.currentEnergies)
        self.output.saveDoS(Es, densitiesOfStates, self.simParams, mcs)


    def saveIons(self, mcs):
        if mcs % self.simParams.savingIonsMcsInterval == 0:
            self.output.saveIons(self)