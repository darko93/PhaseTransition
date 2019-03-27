import os
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import Input as input
import Path as path

Tc = 2.269
epochs = 50
trainSpinsDic = {}
trainLabelsDic = {}
testSpinsDic = {}
testLabelsDic = {}
allTrainSpinsConfigs = []
allTrainLabels = []
allTestSpinsConfigs = []
allTestLabels = []

def GetFirstKeyInDictListLength(dic):
    firstKey = list(dic)[0]
    return len(dic[firstKey])

def ReadSpins():
    spinsDic = dict()
    spinsDirPath = path.spinsDirPath
    for spinsFileName in os.listdir(spinsDirPath):
        spinsFilePath = os.path.join(spinsDirPath, spinsFileName)
        L, T, spinsConfigs = input.ReadSpins(spinsFilePath)
        spinsDic[T]= spinsConfigs
    return spinsDic

def PrepareSpinsData():
    spinsDic = ReadSpins()
    spinsConfigsAmount = GetFirstKeyInDictListLength(spinsDic)
    labelsDic = dict()
    for T in spinsDic:
        #labelsDic[T] = np.zeros((spinsConfigsAmount, 2), dtype=int)
        if T < Tc:
            labelsDic[T] = np.tile(np.array([1, 0]), (spinsConfigsAmount, 1))
        else:
            labelsDic[T] = np.tile(np.array([0, 1]), (spinsConfigsAmount, 1))
    return spinsDic, labelsDic

def PrepareSplittedSpinsData():
    global trainSpinsDic, trainLabelsDic, testSpinsDic, testLabelsDic 
    global allTrainSpinsConfigs, allTrainLabels, allTestSpinsConfigs, allTestLabels
    trainSpinsDic, trainLabelsDic = PrepareSpinsData()
    spinsConfigsAmount = GetFirstKeyInDictListLength(trainSpinsDic)
    lastTrainingIndex = int(0.7 * spinsConfigsAmount)
    testSpinsDic = dict()
    testLabelsDic = dict()
    for T in trainSpinsDic:
        testSpinsDic[T] = trainSpinsDic[T][lastTrainingIndex:]
        trainSpinsDic[T] = trainSpinsDic[T][:lastTrainingIndex]
        testLabelsDic[T] = trainLabelsDic[T][lastTrainingIndex:]
        trainLabelsDic[T] = trainLabelsDic[T][:lastTrainingIndex]

        allTrainSpinsConfigs.extend(trainSpinsDic[T])
        allTrainLabels.extend(trainLabelsDic[T])
        allTestSpinsConfigs.extend(testSpinsDic[T])
        allTestLabels.extend(testLabelsDic[T])

        testSpinsDic[T] = np.array(testSpinsDic[T])
        trainSpinsDic[T] = np.array(trainSpinsDic[T])
        testLabelsDic[T] = np.array(testLabelsDic[T])
        trainLabelsDic[T] = np.array(trainLabelsDic[T])

    allTrainSpinsConfigs = np.array(allTrainSpinsConfigs)
    allTrainLabels = np.array(allTrainLabels)
    allTestSpinsConfigs = np.array(allTestSpinsConfigs)
    allTestLabels = np.array(allTestLabels)


def TrainEvaluatePredict():
    PrepareSplittedSpinsData()    

    # 1. define the network
    model = tf.keras.models.Sequential()
    model.add(tf.keras.layers.Dense(10, input_dim=900, activation=tf.nn.relu))
    model.add(tf.keras.layers.Dense(100, activation=tf.nn.relu))
    model.add(tf.keras.layers.Dense(2, activation=tf.nn.sigmoid))
    # 2. compile the network
    model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
    # 3. fit the network
    history = model.fit(allTrainSpinsConfigs, allTrainLabels, epochs=epochs, batch_size=20)
    # 4. evaluate the network
    loss, accuracy = model.evaluate(allTestSpinsConfigs, allTestLabels)
    print("\nLoss: %.2f, Accuracy: %.2f%%" % (loss, accuracy*100))
    # 5. make predictions
    avePredictions = dict()
    for T, testSpinsConfigs in testSpinsDic.items():
        print("T=" + str(T))
        probabilities = model.predict(testSpinsConfigs)
        predictions = np.array([np.round(x) for x in probabilities])
        avePredictions[T] = np.average(predictions, axis=0)
        accuracy = np.mean(predictions == testLabelsDic[T])
        print("Prediction Accuracy: %.2f%%" % (accuracy*100))
    return avePredictions

avePredictions = TrainEvaluatePredict()
Ts = avePredictions.keys()
lowTNeuronActivities = [item[1][0] for item in avePredictions.items()]
highTNeuronActivities = [item[1][1] for item in avePredictions.items()]
plt.plot(Ts, lowTNeuronActivities, "b-^", Ts, highTNeuronActivities, "r-x")
plt.show()