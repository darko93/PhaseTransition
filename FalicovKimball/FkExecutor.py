from FkSimulationParameters import FkSimulationParameters
from FalicovKimballModel import FalicovKimballModel
import matplotlib.pyplot as plt

def main():
    simParams = FkSimulationParameters(0.05, 0.05, 1, 0, 50, 20, 8, 1)
    fkModel = FalicovKimballModel()
    Es, aveDensityOfStates = fkModel.CalculateAverageDensityOfStates(simParams)
    plt.plot(Es, aveDensityOfStates)
    plt.show()

if __name__ == "__main__":
    main()