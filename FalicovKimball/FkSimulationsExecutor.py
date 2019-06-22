class FkSimulationsExecutor:

    def __init__(self, fkModel):
        self.fkModel = fkModel

    
    def fullSimulation(self, simParams, initIons = None):
        self.fkModel.initialize(simParams, initIons)

        ## saveDoS is True (below)

        if simParams.saveMeantimeQuantities and simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()
                
                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)
                self.fkModel.calculateAndSaveDoS()
                self.fkModel.saveIons(mcs)

        elif simParams.saveMeantimQuantities and simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)
                self.fkModel.calculateAndSaveDoS()


        elif not simParams.saveMeantimQuantities and simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.calculateAndSaveDoS()
                self.fkModel.saveIons(mcs)


        elif not simParams.saveMeantimQuantities and simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.calculateAndSaveDoS()

        ## saveDoS is False (below)

        elif simParams.saveMeantimeQuantities and not simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()
                
                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)
                self.fkModel.saveIons(mcs)

        elif simParams.saveMeantimQuantities and not simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()
                
                self.fkModel.calculateAndSaveMeantimeQuantities(mcs)


        elif not simParams.saveMeantimQuantities and not simParams.saveDoS and simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()

                self.fkModel.saveIons(mcs)

        elif not simParams.saveMeantimQuantities and not simParams.saveDoS and not simParams.saveIons:
            for mcs in range(1, simParams.mcsAmount + 1):
                for i in range(simParams.N):
                    self.fkModel.metropolisStep()