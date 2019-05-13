import matplotlib.pyplot as plt
import Input as input
import Path as path

def PlotActivities():
    Ts, lowTActivitiesDic, highTActivitiesDic = input.ReadNeuronsActivities(path.activitiesFilePath)
    
    plt.plot(Ts, lowTActivitiesDic[10], "b-x", Ts, highTActivitiesDic[10], "r-x",\
             Ts, lowTActivitiesDic[20], "b-^", Ts, highTActivitiesDic[20], "r-^",\
             Ts, lowTActivitiesDic[30], "b-o", Ts, highTActivitiesDic[30], "r-o",\
             Ts, lowTActivitiesDic[40], "b-d", Ts, highTActivitiesDic[40], "r-d",\
             Ts, lowTActivitiesDic[50], "b-s", Ts, highTActivitiesDic[50], "r-s")
    plt.xlabel('T')
    plt.ylabel('Output layer neurons activities')
    plt.show()
    

def PlotAccuracies():
    Ts, predictAccDic = input.ReadAccuracies(path.predictAccsFilePath)

    plt.plot(Ts, predictAccDic[10], "g-x",\
             Ts, predictAccDic[20], "c-^",\
             Ts, predictAccDic[30], "b-o",\
             Ts, predictAccDic[40], "m-d",\
             Ts, predictAccDic[50], "r-s")
    plt.xlabel('T')
    plt.ylabel('Prediction accuracies')
    plt.show()

PlotActivities()
PlotAccuracies()