import os
import Path as path
import Input as input
import Output as output
import Quantities as quant


def GetQuantitiesFilePath(L, T, h):
    quantitiesFileName = "Quantities_L=" + str(L) + "_T=" + "{0:.3f}".format(T) + "_h=" + "{0:.3f}".format(h) + path.dataFileExtension
    quantitiesFilePath = os.path.join(path.quantitiesDirPath, quantitiesFileName)
    return quantitiesFilePath


def CalculateAllXs(TQuantitiesDirPath):
    Ls = [10, 20, 30, 40, 50]
    minT = 2.269 #0.5
    maxT = 2.269 #4.01
    TStep = 0.1
    T = minT
    h = 0
    X = 0.0
    Ts = []
    Ms = []
    XsDic = {}

    for L in Ls:
        T = minT
        Xs = []
        while (T <= maxT):
            quantitiesFilePath = GetQuantitiesFilePath(L, T, h)
            print(quantitiesFilePath)

            firstL = L == Ls[0]
            if firstL:
                Ts.append(T)

            if firstL and T == minT:
                # Read header only from the first data file
                headerLines, Ms = input.ReadMsWithHeader(quantitiesFilePath)
            else:
                Ms = input.ReadMs(quantitiesFilePath)
            if "Repeat" not in quantitiesFilePath:
                #Use only termalized data from
                print("Ms length before cut:" + str(len(Ms)))
                Ms = Ms[50000:]
                print("Ms length after cut:" + str(len(Ms)))

            X = quant.MagneticSusceptibility(L, T, Ms)
            Xs.append(X)
            
            T += TStep
            T = round(T, 3)
        XsDic[L] = Xs
        
    return Ts, XsDic, headerLines


def CreateXsLines(Ts, XsDic, headerLines):
    XLines = []
    
    header = "#" + "{0: >9}".format("T")
    for L in XsDic:
        header += "{0: >30}".format("X_L=" + str(L))

    headerLines.append("\n\n" + header + "\n\n")
    for headerLine in headerLines:
        XLines.append(headerLine)

    for i in range(0, len(Ts)):
        XLine = "{0: >10}".format(str(Ts[i]))
        for Xs in XsDic.values():
            XLine += "{0: >30}".format(repr(Xs[i]))
        XLine += "\n"
        XLines.append(XLine)
    
    return XLines


def CalculateAllMagneticSusceptibilities():
    TQuantitiesDirPath = path.TQuantitiesDirPath
    #path.RecreateDir(TQuantitiesDirPath)
    TQuantitiesFileName = os.path.join(TQuantitiesDirPath, "X" + path.dataFileExtension)
    Ts, XsDic, headerLines = CalculateAllXs(TQuantitiesDirPath)
    XLines = CreateXsLines(Ts, XsDic, headerLines)
    output.SaveLinesToFile(XLines, TQuantitiesFileName)
    

CalculateAllMagneticSusceptibilities()