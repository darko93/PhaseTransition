class FkSimulationsExecutor:

    def __init__(self, fkModel):
        self.fkModel = fkModel

    
    def printMcs(self, mcs):
        print("mcs={0}".format(mcs), end="\r", flush=True)

    
    def fullSimulation(self, simParams, initIons = None):
        self.fkModel.initialize(simParams, initIons)

        ## saveDoS is True (below)

        if simParams.saveMeantimeQuantities and simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()
                
                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)
                self.fkModel.calculateAndSaveDoS(mcs)
                self.fkModel.saveIons(mcs)

        elif simParams.saveMeantimeQuantities and simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)
                self.fkModel.calculateAndSaveDoS(mcs)


        elif not simParams.saveMeantimeQuantities and simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.calculateAndSaveDoS(mcs)
                self.fkModel.saveIons(mcs)


        elif not simParams.saveMeantimeQuantities and simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.calculateAndSaveDoS(mcs)

        ## saveDoS is False (below)

        elif simParams.saveMeantimeQuantities and not simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()
                
                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)
                self.fkModel.saveIons(mcs)

        elif simParams.saveMeantimeQuantities and not simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()
                
                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)


        elif not simParams.saveMeantimeQuantities and not simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.saveIons(mcs)

        elif not simParams.saveMeantimeQuantities and not simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                self.printMcs(mcs)

                for i in range(simParams.N):
                    self.fkModel.metropolisStep()