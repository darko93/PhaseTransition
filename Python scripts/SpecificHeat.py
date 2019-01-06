import os
import Path as path
import Input as input

quantitiesDirPath = path.quantitiesDirPath

def GetQuantitiesFilePath(L, T, h):
    quantitiesFileName = "Quantities_L=" + str(L) + "_T=" + "{0:.3f}".format(T) + "_h=" + "{0:.3f}".format(h) + path.dataFileExtension
    quantitiesFilePath = os.path.join(path.quantitiesDirPath, quantitiesFileName)
    return quantitiesFilePath


def ReadQuantities(quantitiesFilePath):
    quantitiesLines = input.ReadFileLines(quantitiesFilePath)

    ts = []
    Hs = []
    Ms = []
    T = 0.0
    L = 0

    i = 0
    for quantitiesLine in quantitiesLines:
        if i == 0:
            quantitiesLine = quantitiesLine.rstrip()
            TString = quantitiesLine[2:]
            T = float(TString)
        elif i == 4:
            quantitiesLine = quantitiesLine.rstrip()
            LString = quantitiesLine[12:]
            L = int(LString)
        elif i > 8:
            quantitiesArray = quantitiesLine.split()
            tString = quantitiesArray[0]
            t = int(tString)
            HString = quantitiesArray[1]
            H = float(HString)
            MString = quantitiesArray[2]
            M = float(MString)
            ts.append(t)
            Hs.append(H)
            Ms.append(M)
        i = 1 + i
    return ts, Hs, Ms, T, L


def CalculateCv(quantitiesFilePath):
    ts, Hs, Ms, T, L = ReadQuantities(quantitiesFilePath)
    kB = 1
    sumH = 0.0
    sumH2 = 0.0
    mcsAmount = len(Hs)
    iH = 0.0
    for i in range(0, mcsAmount):
        iH = Hs[i]
        sumH += iH
        sumH2 += iH * iH

    aveH = sumH / mcsAmount
    aveH2 = sumH2 / mcsAmount
    N = L * L
    Cv = (aveH2 - aveH * aveH) / (N * kB * T * T)

    return Cv


def CalculateCvs():
    L = 20
    minT = 0.5
    maxT = 4.01
    TStep = 0.1
    T = minT
    h = 0
    Cvs = []
    Ts = []
    Cv = 0.0
    while (T <= maxT):
        quantitiesFilePath = GetQuantitiesFilePath(L, T, h)
        Cv = CalculateCv(quantitiesFilePath)
        Cvs.append(Cv)
        Ts.append(T)

        print("T=" + "{0:.3f}".format(T))

        T += TStep

    return Ts, Cvs