from FkInputData import FkInputData

class FkInput:

    def readFileLines(self, filePath):
        fileLines = []
        with open(filePath) as file:
            fileLines = file.readlines()
        return fileLines

   
    def readStringValue(self, dataLine):
        indexOfEquals = dataLine.index("=")
        stringValue = dataLine.rstrip()[indexOfEquals + 1:]
        return stringValue

   
    def readIntValue(self, dataLine):
        floatValue = int(self.readStringValue(dataLine))
        return floatValue

   
    def readFloatValue(self, dataLine):
        floatValue = float(self.readStringValue(dataLine))
        return floatValue

   
    def toBool(self, strVal):
        boolValue = strVal.lower() in ["true", "1", "yes"]
        return boolValue

   
    def readBoolValue(self, dataLine):
        boolValue = self.toBool(self.readStringValue(dataLine))
        return boolValue

   
    def readTRangeDict(self, fileLines):
        TRangeDict = dict()
        for line in fileLines:
            TRange = line.split(";")
            U = float(self.readStringValue(TRange[0]))
            minT = float(self.readStringValue(TRange[1]))
            maxT = float(self.readStringValue(TRange[2]))
            TRangeDict[U] = [minT, maxT]
        return TRangeDict

   
    def readInputData(self, inputDataFilePath):
        fileLines = self.readFileLines(inputDataFilePath)
        saveMeantimeQuantities = self.readBoolValue(fileLines[0])
        meantimeQuantitiesFilePathPattern = self.readStringValue(fileLines[1])
        saveIons = self.readBoolValue(fileLines[2])
        ionsFilePathPattern = self.readStringValue(fileLines[3])
        savingIonsMcsInterval = self.readIntValue(fileLines[4])
        reuseIons = self.readBoolValue(fileLines[5])
        dE = self.readFloatValue(fileLines[6])
        gamma = self.readFloatValue(fileLines[7])
        mu = self.readFloatValue(fileLines[8])
        elConc = self.readFloatValue(fileLines[9])
        mcsAmount = self.readIntValue(fileLines[10])
        minL = self.readIntValue(fileLines[11])
        maxL = self.readIntValue(fileLines[12])
        LStep = self.readIntValue(fileLines[13])
        TStep = self.readFloatValue(fileLines[14])
        TRangeDict = self.readTRangeDict(fileLines[15:])

        inputData = FkInputData()
        inputData.saveMeantimeQuantities = saveMeantimeQuantities
        inputData.meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern
        inputData.saveIons = saveIons
        inputData.ionsFilePathPattern = ionsFilePathPattern
        inputData.savingIonsMcsInterval = savingIonsMcsInterval
        inputData.reuseIons = reuseIons
        inputData.dE = dE
        inputData.gamma = gamma
        inputData.mu = mu
        inputData.elConc = elConc
        inputData.mcsAmount = mcsAmount
        inputData.minL = minL
        inputData.maxL = maxL
        inputData.LStep = LStep
        inputData.TStep = TStep
        inputData.TRangeDict = TRangeDict
        return inputData