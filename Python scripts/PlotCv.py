from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import SpecificHeat as Cv

def PlotCv():
    Ts, Cvs = Cv.CalculateCvs()
    Ts = Ts[1:]
    Cvs = Cvs[1:]
    plt.plot(Ts, Cvs)
    plt.xlabel('T')
    plt.ylabel('Cv')
    plt.title('Cv(T)')
    plt.show()


PlotCv()
