import os
import Path as path
import Input as input
import Output as output
import Quantities as quant


def GetQuantitiesFilePath(L, T, h):
    quantitiesFileName = "Quantities_L=" + str(L) + "_T=" + "{0:.3f}".format(T) + "_h=" + "{0:.3f}".format(h) + path.dataFileExtension
    quantitiesFilePath = os.path.join(path.quantitiesDirPath, quantitiesFileName)
    return quantitiesFilePath


def CalculateAllB4(TQuantitiesDirPath):
    Ls = [10, 20, 30, 40, 50]
    minT = 2.269 #0.5
    maxT = 2.269 #4.01
    TStep = 0.1
    T = minT
    h = 0
    binder = 0.0
    Ts = []
    Ms = []
    bindersDic = {}

    for L in Ls:
        T = minT
        binders = []
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

            binder = quant.BinderCumulant4(Ms)
            binders.append(binder)
            
            T += TStep
            T = round(T, 3)
        bindersDic[L] = binders
        
    return Ts, bindersDic, headerLines


def CreateBindersLines(Ts, bindersDic, headerLines):
    binderLines = []
    
    header = "#" + "{0: >9}".format("T")
    for L in bindersDic:
        header += "{0: >30}".format("B4_L=" + str(L))

    headerLines.append("\n\n" + header + "\n\n")
    for headerLine in headerLines:
        binderLines.append(headerLine)

    for i in range(0, len(Ts)):
        binderLine = "{0: >10}".format(str(Ts[i]))
        for binders in bindersDic.values():
            binderLine += "{0: >30}".format(repr(binders[i]))
        binderLine += "\n"
        binderLines.append(binderLine)
    
    return binderLines


def CalculateAllBinderCumulants4():
    TQuantitiesDirPath = path.TQuantitiesDirPath
    #path.RecreateDir(TQuantitiesDirPath)
    TQuantitiesFileName = os.path.join(TQuantitiesDirPath, "B4" + path.dataFileExtension)
    Ts, bindersDic, headerLines = CalculateAllB4(TQuantitiesDirPath)
    binderLines = CreateBindersLines(Ts, bindersDic, headerLines)
    output.SaveLinesToFile(binderLines, TQuantitiesFileName)
    

CalculateAllBinderCumulants4()
