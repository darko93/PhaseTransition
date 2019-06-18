from FkInputData import FkInputData

class FkOutput:

    PRECISION_IN_FILE_NAME = 3
    FLOAT_VAL_FORMAT_IN_FILE_NAME = ""
    QUANTITIES_BUFFER_SIZE = 10000
    IONS_BUFFER_SIZE = 1000
    DATA_FILE_EXTENSION = ".dat"

    quantitiesFilePathPattern = ""
    ionsFilePathPattern = ""

    quantitiesCount = 0
    quantities = list()
    ionicConfigsCount = 0
    ionicConfigs = list()


    def __init__(self):
        self.FLOAT_VAL_FORMAT_IN_FILE_NAME = "{0:." + str(self.PRECISION_IN_FILE_NAME) + "f}"

    def getFilePath(self, filePathPattern, simParams):
        UStr = self.FLOAT_VAL_FORMAT_IN_FILE_NAME.format(simParams.U)
        TStr = self.FLOAT_VAL_FORMAT_IN_FILE_NAME.format(simParams.T)
        
        filePath = filePathPattern + "_L=" + str(simParams.L) + "_U" + UStr + "_T" + TStr

        if simParams.repeat == 1:
            filePath += self.DATA_FILE_EXTENSION
        else:
            filePath += "_Repeat=" + str(simParams.repeat) + self.DATA_FILE_EXTENSION
        
        return filePath

    def createIonsFile(self, ionsFilePathPattern, simParams):
        self.ionsFilePathPattern = ionsFilePathPattern
        filePath = self.getFilePath(ionsFilePathPattern, simParams)
        with open(filePath) as file:
            header = "#t={0}\n#L={1}\n#U={2}\n#T={3}\n#kB={4}\n#ionsMcsInterval={5}\n\n\n"\
                .format(simParams.t, simParams.L, simParams.U, simParams.T, simParams.kB, simParams.savingIonsMcsInterval)
            file.write(header)

    def saveIons(self, fkModel):
        ions = list()
        ions.append("\n")
        N = fkModel.simParams.N
        for i in range(N):
            ions.append(str(fkModel.ions[i]))
        ionsStr = "".join(ions)
        self.ionicConfigs.append(ionsStr)
        
        self.ionicConfigsCount += 1
        if self.ionicConfigsCount >= self.IONS_BUFFER_SIZE:
            self.flushIons(fkModel.simParams)

    def flushIons(self, simParams):
        if self.ionicConfigsCount > 0:
            ionsFilePath = self.getFilePath(self.ionsFilePathPattern, simParams)
            ionsStr = "".join(self.ionicConfigs)
            with open(ionsFilePath) as file:
                file.write(ionsStr)
            self.ionicConfigs.clear()
            self.ionicConfigsCount = 0

    def createMeantimeQuantitiesFile(self, quantitiesFilePathPattern, simParams):
        self.quantitiesFilePathPattern = quantitiesFilePathPattern # Setting it here and using in save method
        filePath = self.getFilePath(quantitiesFilePathPattern, simParams)
        with open(filePath, "w") as file:
            header = "#t={0}\n#L={1}\n#U={2}\n#T={3}\n#kB={4}\n\n\n#MCS\tE\tg1\n\n"\
                .format(simParams.t, simParams.L, simParams.U, simParams.T, simParams.kB)
            file.write(header)

    def saveMeantimQuantities(self, quantities, simParams, mcs):
        quantitiesLine = "{0} {1} {2}".format(mcs, quantities.E, quantities.g1)
        self.quantities.append(quantitiesLine)

        self.quantitiesCount += 1
        if self.quantitiesCount >= self.QUANTITIES_BUFFER_SIZE:
            self.flushMeantimeQuantities(simParams)

    def flushMeantimeQuantities(self, simParams):
        if self.quantitiesCount > 0:
            quantitiesFilePath = self.getFilePath(self.quantitiesFilePathPattern, simParams)
            quantitiesStr = "".join(self.quantities)
            with open(quantitiesFilePath) as file:
                file.write(quantitiesStr)
            self.quantities.clear()
            self.quantitiesCount = 0
