import matplotlib.pyplot as plt
import Input as input

def PlotAutocorrelation(autocorrelationFilePath):
    ts, EAutocorrel, Mautocorrel = input.ReadThreeColumns(autocorrelationFilePath)

    plt.plot(ts, EAutocorrel)
    plt.xlabel("t")
    plt.ylabel("EAutocorrel")
    plt.title("Energy autocorrelation function")
    plt.show()

    plt.plot(ts, Mautocorrel)
    plt.xlabel("t")
    plt.ylabel("EAutocorrel")
    plt.title("Magnetization autocorrelation function")
    plt.show()

PlotAutocorrelation("IsingAutocorrelation2/Autocorrelation_L=30_T=3.00_h=0.00.dat")
