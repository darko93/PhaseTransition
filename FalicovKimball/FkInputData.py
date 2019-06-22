from FkSimulationParameters import FkSimulationParameters

class FkInputData:
    saveMeantimeQuantities = False
    meantimeQuantitiesFilePathPattern = ""
    saveIons = False
    IonsFilePathPattern = ""
    savingIonsMcsInterval = 0
    reuseIons = False
    repeats = 0
    dE = 0.0
    gamma = 0.0
    mu = 0.0
    elConc = 0.0
    mcsAmount = 0
    minL = 0
    maxL = 0
    LStep = 0
    TStep = 0.0
    TRangeDict = dict() # Key - U; Value - tuple, tuple[0] - minT, tuple[1] - maxT

  
    def addTRange(self, U, minT, maxT):
        self.TRangeDict[U] = [minT, maxT]

  
    def toFirstSimParams(self):
        simParams = FkSimulationParameters()
        simParams.saveMeantimeQuantities = self.saveMeantimeQuantities
        simParams.saveIons = self.saveIons
        simParams.savingIonsMcsInterval = self.savingIonsMcsInterval
        simParams.reuseIons = self.reuseIons
        simParams.repeat = 1
        simParams.dE = self.dE
        simParams.gamma = self.gamma
        simParams.mu = self.mu
        simParams.elConc = self.elConc
        simParams.mcsAmount = self.mcsAmount
        simParams.setL(self.minL)
        firstU = list(self.TRangeDict.keys())[0]
        simParams.U = firstU
        simParams.setT(self.TRangeDict[firstU][0]) # min T for first U
        return simParams

  
    def toNextSimParams(self, simParams):
        nextRepeatNr = simParams.repeat + 1
        if nextRepeatNr <= self.repeats:
            simParams.repeat += 1
            return True
        simParams.repeat = 1

        isInRange = False
        nextT = simParams.T + self.TStep
        minT = self.TRangeDict[simParams.U][0]
        maxT = self.TRangeDict[simParams.U][1]
        UsList = list(self.TRangeDict.keys())
        isInRange = nextT <= maxT
        if not isInRange or minT == maxT:
            UIndex = UsList.index(simParams.U)
            nextUIndex = UIndex + 1
            if nextUIndex < len(UsList):
                nextU = UsList[nextUIndex]
                simParams.U = nextU
                simParams.T = self.TRangeDict[nextU][0] # min T for next U
                return True
            else:
                nextL = simParams.L + self.LStep
                if nextL > self.maxL:
                    return False
                simParams.L = nextL
                firstU = UsList[0]
                simParams.U = firstU
                simParams.T = self.TRangeDict[firstU][0] # min T for first U
                return True
        simParams.T = nextT
        return True