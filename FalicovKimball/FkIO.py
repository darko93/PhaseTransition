class FkIO:

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
        floatValue = float(self.readStringValue(dataLine))
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

    def readInputData(self, inputDataFilePath):
        inputDataLines = self.readFileLines(inputDataFilePath)
        for line in inputDataLines:
            saveMeantimeQuantitites = self.readBoolValue(line)
            meantimeQuantitiesFilePathPattern = self.readStringValue(line)
            saveIonicConfig = self.readBoolValue(line)
            ionicConfigFilePathPattern = self.readStringValue(line)
            savingIonicConfigMcsInterval = self.readIntValue(line)
            dE = self.readFloatValue(line)
            gamma = self.readFloatValue(line)
            mu = self.readFloatValue(line)
            mcsAmount = self.readIntValue(line)
            minL = self.readIntValue(line)
            maxL = self.readIntValue(line)
            LStep = self.readIntValue(line)
            TStep = self.readFloatValue(line)
            # read T ranges for each U
            