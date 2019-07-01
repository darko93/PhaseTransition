from FkSimulationsExecutor import FkSimulationsExecutor
from FkSimulationParameters import FkSimulationParameters
from FkInputData import FkInputData
from FkInput import FkInput
from FkOutput import FkOutput
from FalicovKimballModel import FalicovKimballModel

def main():
    input = FkInput()
    inputData = input.readInputData("FalicovKimballInput.txt")
    simParams = inputData.toFirstSimParams()
    
    print("kB={0}\tt={1}\telConc={2}".format(simParams.kB, simParams.t, simParams.elConc))
    
    output = FkOutput()
    fkModel = FalicovKimballModel(output)
    fkSimExecutor = FkSimulationsExecutor(fkModel)
    
    nextSimParamsExist = True
    while nextSimParamsExist:
        print("L={0}\tU={1}\tT={2}\tRepeat={3}".format(simParams.L, simParams.U, simParams.T, simParams.repeat))
        
        if simParams.saveMeantimeQuantities:
            output.createMeantimeQuantitiesFile(inputData.meantimeQuantitiesFilePathPattern, simParams)
        if simParams.saveDoS:
            output.createDoSFile(inputData.DoSFilePathPattern, simParams)
        if simParams.saveIons:
            output.createIonsFile(inputData.ionsFilePathPattern, simParams)

        fkSimExecutor.fullSimulation(simParams)

        output.flushMeantimeQuantities(simParams)
        output.flushIons(simParams)

        nextSimParamsExist = inputData.toNextSimParams(simParams)

    print("Finished")

    # simParams = FkSimulationParameters()
    # simParams.dE = 0.05
    # simParams.gamma = 0.05
    # simParams.kB = 1
    # simParams.t = 1
    # simParams.mu = 0
    # simParams.mcsAmount = 50
    # simParams.setL(20)
    # simParams.U = 20
    # simParams.setT(1)
    # simParams.saveMeantimeQuantities = True
    # simParams.saveIons = True
    # fkModel = FalicovKimballModel()
    # fkModel.fullSimulation(simParams)

    # fkModel.initialize(simParams)
    # Es, aveDensityOfStates = fkModel.averageDensityOfStates()
    # plt.plot(Es, aveDensityOfStates)
    # plt.show()
    
    #fkModel = FalicovKimballModel()
    #occupiedSites, emptySites = fkModel.getOccupiedAndEmptySitesIndices(10)
    #print(occupiedSites)
    #print(emptySites)

if __name__ == "__main__":
    main()