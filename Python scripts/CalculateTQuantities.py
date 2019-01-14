import os
import Path as path
import Input as input
import Output as output
import TQuantities as quant

def GetQuantitiesFilePath(L, T, h):
    quantitiesFileName = "Quantities_L=" + str(L) + "_T=" + "{0:.3f}".format(T) + "_h=" + "{0:.3f}".format(h) + path.dataFileExtension
    quantitiesFilePath = os.path.join(path.quantitiesDirPath, quantitiesFileName)
    return quantitiesFilePath


def CalculateTQuantities(TQuantitiesDirPath, ReadQuantityWithHeaderFunc, TQuantityFunc):
    Ls = [10, 20, 30, 40, 50]
    minT = 2.269 #0.5
    maxT = 2.269 #4.01
    TStep = 0.1
    T = minT
    h = 0
    firstL = False
    TQuantity = 0.0
    Ts = []
    Es = []
    TQuantitiesDic = {}

    for L in Ls:
        T = minT
        TQuantities = []
        while (T <= maxT):
            quantitiesFilePath = GetQuantitiesFilePath(L, T, h)
            print(quantitiesFilePath)

            firstL = L == Ls[0]
            if firstL:
                Ts.append(T)

            if firstL and T == minT:
                # Read header only from the first data file
                headerLines, Es = ReadQuantityWithHeaderFunc(quantitiesFilePath)
            else:
                Es = input.ReadEs(quantitiesFilePath)

            if "Repeat" not in quantitiesFilePath:
                #Use only termalized data
                print("TQuantities length before cut:" + str(len(Es)))
                Es = Es[50000:]
                print("TQuantities length after cut:" + str(len(Es)))

            TQuantity = TQuantityFunc(L, T, Es)
            TQuantities.append(TQuantity)
            
            T += TStep
            T = round(T, 3)
        TQuantitiesDic[L] = TQuantities
        
    return Ts, TQuantitiesDic, headerLines


def CreateTQuantitiesLines(Ts, TQuantitiesDic, headerLines, quantityName):
    TQuantityLines = []

    for headerLine in headerLines:
        TQuantityLines.append(headerLine)

    header = "#" + "{0: >9}".format("T")
    for L in TQuantitiesDic:
        header += "{0: >30}".format(quantityName + "_L=" + str(L))

    TQuantityLines.append("\n\n" + header + "\n\n")

    for i in range(0, len(Ts)):
        TQuantityLine = "{0: >10}".format(str(Ts[i]))
        for TQuantities in TQuantitiesDic.values():
            TQuantityLine += "{0: >30}".format(repr(TQuantities[i]))
        TQuantityLine += "\n"
        TQuantityLines.append(TQuantityLine)
    
    return TQuantityLines


def CalculateAndSaveTQuantities(quantityName, ReadQuantityWithHeaderFunc, TQuantityFunc):
    TQuantitiesDirPath = path.TQuantitiesDirPath
    #path.RecreateDir(TQuantitiesDirPath)
    TQuantitiesFileName = os.path.join(TQuantitiesDirPath, quantityName + path.dataFileExtension)
    Ts, TQuantitiesDic, headerLines = CalculateTQuantities(TQuantitiesDirPath, ReadQuantityWithHeaderFunc, TQuantityFunc)
    TQuantityLines = CreateTQuantitiesLines(Ts, TQuantitiesDic, headerLines, quantityName)  
    output.SaveLinesToFile(TQuantityLines, TQuantitiesFileName)
    

def CalculateAndSaveCv():
    CalculateAndSaveTQuantities("Cv", input.ReadEsWithHeader, quant.SpecificHeat)

def CalculateAndSaveX():
    CalculateAndSaveTQuantities("X", input.ReadMsWithHeader, quant.MagneticSusceptibility)

def CalculateAndSaveAveMPerSite():
    CalculateAndSaveTQuantities("avem", input.ReadMsWithHeader, quant.AveMPerSite)

def CalculateAndSaveBinderCumulant4():
    CalculateAndSaveTQuantities("B4", input.ReadMsWithHeader, quant.BinderCumulant4)