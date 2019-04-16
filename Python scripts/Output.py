def SaveLinesToFile(lines, filePath):
    with open(filePath, "w") as file:
        for line in lines:
            file.write(line)

def SaveActivities(filePath, activitiesDic):
    with open(filePath, "w") as file:
        file.write("#T    lowTActivity    highTActivity")
        for L, activitiesDicT in activitiesDic.items():
            file.write("\n\nL=" + str(L))
            for T in activitiesDicT:
                file.write("\n" + str(T) + " " + str(activitiesDicT[T][0]) + " " + str(activitiesDicT[T][1]))

def SavePredictAccuracies(filePath, predictAccDic):
    with open(filePath, "w") as file:
        file.write("#T predictAcc")
        for L, predictAccDicT in predictAccDic.items():
            file.write("\n\nL=" + str(L))
            for T, accuracy in predictAccDicT.items():
                file.write("\n" + str(T) + " " + str(accuracy))