import matplotlib.pyplot as plt
import Input as input
import Path as path

def PlotActivities():
    Ts, lowTActivitiesDic, highTActivitiesDic = input.ReadNeuronsActivities(path.activitiesFilePath)
    
    plt.plot(Ts, lowTActivitiesDic[10], "b-x", label="L=10")
    plt.plot(Ts, highTActivitiesDic[10], "r-x")
    plt.plot(Ts, lowTActivitiesDic[20], "b-^", label="L=20")
    plt.plot(Ts, highTActivitiesDic[20], "r-^")
    plt.plot(Ts, lowTActivitiesDic[30], "b-o", label="L=30")
    plt.plot(Ts, highTActivitiesDic[30], "r-o")
    plt.plot(Ts, lowTActivitiesDic[40], "b-d", label="L=40")
    plt.plot(Ts, highTActivitiesDic[40], "r-d")
    plt.plot(Ts, lowTActivitiesDic[50], "b-s", label="L=50")
    plt.plot(Ts, highTActivitiesDic[50], "r-s")
    plt.legend(loc='center right')
    plt.xlabel('T')
    plt.ylabel('Output layer neurons activities')
    plt.show()
    

def PlotAccuracies():
    Ts, predictAccDic = input.ReadAccuracies(path.predictAccsFilePath)

    plt.plot(Ts, predictAccDic[10], "g-x", label="L=10")
    plt.plot(Ts, predictAccDic[20], "c-^", label="L=20")
    plt.plot(Ts, predictAccDic[30], "r-o", label="L=30")
    plt.plot(Ts, predictAccDic[40], "m-d", label="L=40")
    plt.plot(Ts, predictAccDic[50], "b-s", label="L=50")
    plt.legend(loc='center right')
    plt.xlabel('T')
    plt.ylabel('Prediction accuracies')
    plt.show()

PlotActivities()
PlotAccuracies()