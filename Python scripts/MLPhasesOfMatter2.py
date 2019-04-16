import os
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import Input as input
import Path as path
import Output as output

Tc = 2.269
epochs = 30
trainSpinsDic = dict()
trainLabelsDic = dict()
testSpinsDic = dict()
testLabelsDic = dict()
allTrainSpinsConfigs = dict()
allTrainLabels = dict()
allTestSpinsConfigs = dict()
allTestLabels = dict()

def GetFirstKeyInDictListLength(dic):
    firstKey = list(dic)[0]
    return len(dic[firstKey])

def ReadSpins():
    spinsDic = dict()
    spinsDirPath = path.spinsDirPath
    for spinsFileName in os.listdir(spinsDirPath):
        print("Reading " + spinsFileName, end="\r", flush=True)
        spinsFilePath = os.path.join(spinsDirPath, spinsFileName)
        L, T, spinsConfigs = input.ReadSpins(spinsFilePath)
        if L not in spinsDic:
            spinsDic[L] = dict()
        spinsDic[L][T] = spinsConfigs
    return spinsDic

def PrepareSpinsData():
    spinsDic = ReadSpins()
    labelsDic = dict()
    for L, spinsDicT in spinsDic.items():
        print("Preparing labels for L=" + str(L), end="\r", flush=True)
        labelsDic[L] = dict()
        spinsConfigsAmount = GetFirstKeyInDictListLength(spinsDicT)
        for T in spinsDicT:
            if T < Tc:
                labelsDic[L][T] = np.tile(np.array([1, 0]), (spinsConfigsAmount, 1))
            else:
                labelsDic[L][T] = np.tile(np.array([0, 1]), (spinsConfigsAmount, 1))
    return spinsDic, labelsDic

def PrepareSplittedSpinsData():
    global trainSpinsDic, trainLabelsDic, testSpinsDic, testLabelsDic 
    global allTrainSpinsConfigs, allTrainLabels, allTestSpinsConfigs, allTestLabels
    trainSpinsDic, trainLabelsDic = PrepareSpinsData()
    for L, trainSpinsDicT in trainSpinsDic.items():
        testSpinsDic[L] = dict()
        testLabelsDic[L] = dict()

        allTrainSpinsConfigs[L] = []
        allTrainLabels[L] = []
        allTestSpinsConfigs[L] = []
        allTestLabels[L] = []

        spinsConfigsAmount = GetFirstKeyInDictListLength(trainSpinsDicT)
        lastTrainingIndex = int(0.7 * spinsConfigsAmount)
        for T in trainSpinsDicT:
            testSpinsDic[L][T] = trainSpinsDic[L][T][lastTrainingIndex:]
            trainSpinsDic[L][T] = trainSpinsDic[L][T][:lastTrainingIndex]
            testLabelsDic[L][T] = trainLabelsDic[L][T][lastTrainingIndex:]
            trainLabelsDic[L][T] = trainLabelsDic[L][T][:lastTrainingIndex]

            allTrainSpinsConfigs[L].extend(trainSpinsDic[L][T])
            allTrainLabels[L].extend(trainLabelsDic[L][T])
            allTestSpinsConfigs[L].extend(testSpinsDic[L][T])
            allTestLabels[L].extend(testLabelsDic[L][T])

            testSpinsDic[L][T] = np.array(testSpinsDic[L][T])
            trainSpinsDic[L][T] = np.array(trainSpinsDic[L][T])
            testLabelsDic[L][T] = np.array(testLabelsDic[L][T])
            trainLabelsDic[L][T] = np.array(trainLabelsDic[L][T])

        allTrainSpinsConfigs[L] = np.array(allTrainSpinsConfigs[L])
        allTrainLabels[L] = np.array(allTrainLabels[L])
        allTestSpinsConfigs[L] = np.array(allTestSpinsConfigs[L])
        allTestLabels[L] = np.array(allTestLabels[L])


def TrainEvaluatePredict():
    PrepareSplittedSpinsData()    

    avePredictDic = dict()
    predictAccDic = dict()

    for L in allTrainSpinsConfigs:
        avePredictDic[L] = dict()
        predictAccDic[L] = dict()

        inputDim = L*L
        # 1. define the network
        model = tf.keras.models.Sequential()
        model.add(tf.keras.layers.Dense(10, input_dim=inputDim, activation=tf.nn.relu))
        model.add(tf.keras.layers.Dense(100, activation=tf.nn.relu))
        model.add(tf.keras.layers.Dense(2, activation=tf.nn.sigmoid))
        # 2. compile the network
        model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
        # 3. 9fit the network
        history = model.fit(allTrainSpinsConfigs[L], allTrainLabels[L], epochs=epochs, batch_size=20)
        # 4. evaluate the network for all Ts
        loss, accuracy = model.evaluate(allTestSpinsConfigs[L], allTestLabels[L])
        print("All Ts: loss=" + str(loss) + "\taccuracy=" + str(accuracy))
        # 5. make predictions (evaluate for each T separately)
        for T, testSpinsConfigs in testSpinsDic[L].items():
            print("T=" + str(T))
            probabilities = model.predict(testSpinsConfigs)
            predictions = np.array([np.round(x) for x in probabilities])
            avePredictDic[L][T] = np.average(predictions, axis=0)
            accuracy = np.mean(predictions == testLabelsDic[L][T])
            predictAccDic[L][T] = accuracy
            print("Prediction Accuracy: %.2f%%" % (accuracy*100))
    return avePredictDic, predictAccDic

def LearnAndPlotResults():
    avePredictDic, predictAccDic = TrainEvaluatePredict()
    Ts = list(avePredictDic.values())[0].keys()

    output.SaveActivities(path.activitiesFilePath, avePredictDic)
    output.SavePredictAccuracies(path.predictAccsFilePath, predictAccDic)
    
    lowTActivitiesDic = dict()
    highTActivitiesDic = dict()
    for L, avePredictionsDicT in avePredictDic.items():
        # item[0] - key, item[1] - value
        # value = zero-one vector of length two, which represents low and high T neurons average activities
        lowTActivitiesDic[L] = [item[1][0] for item in avePredictionsDicT.items()]
        highTActivitiesDic[L] = [item[1][1] for item in avePredictionsDicT.items()]
        predictAccDic[L] = [item[1] for item in predictAccDic[L].items()]

    plt.plot(Ts, lowTActivitiesDic[10], "b-x", Ts, highTActivitiesDic[10], "r-x",\
             Ts, lowTActivitiesDic[20], "b-^", Ts, highTActivitiesDic[20], "r-^",\
             Ts, lowTActivitiesDic[30], "b-o", Ts, highTActivitiesDic[30], "r-o",\
             Ts, lowTActivitiesDic[40], "b-d", Ts, highTActivitiesDic[40], "r-d",\
             Ts, lowTActivitiesDic[50], "b-s", Ts, highTActivitiesDic[50], "r-s")
    plt.show()
    
    plt.plot(Ts, predictAccDic[10], "b-x",\
             Ts, predictAccDic[20], "b-^",\
             Ts, predictAccDic[30], "b-o",\
             Ts, predictAccDic[40], "b-d",\
             Ts, predictAccDic[50], "r-s")
    plt.show()

LearnAndPlotResults()