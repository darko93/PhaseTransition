from FkSimulationParameters import FkSimulationParameters
from FalicovKimballModel import FalicovKimballModel
import matplotlib.pyplot as plt

def main():
    simParams = FkSimulationParameters()
    simParams.dE = 0.05
    simParams.gamma = 0.05
    simParams.kB = 1
    simParams.t = 1
    simParams.mu = 0
    simParams.mcsAmount = 50
    simParams.setL(20)
    simParams.U = 20
    simParams.setT(1)
    simParams.saveMeantimeQuantities = True
    simParams.saveIonicConfig = True
    fkModel = FalicovKimballModel()

    fkModel.fullSimulation(simParams)

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