import os
import Path as path
import Input as input
import Output as output
import Quantities as quant

def GetQuantitiesFilePath(L, T, h):
    quantitiesFileName = "Quantities_L=" + str(L) + "_T=" + "{0:.3f}".format(T) + "_h=" + "{0:.3f}".format(h) + path.dataFileExtension
    quantitiesFilePath = os.path.join(path.quantitiesDirPath, quantitiesFileName)
    return quantitiesFilePath


def CalculateAllAvems(TQuantitiesDirPath):
    Ls = [10, 20, 30, 40, 50]
    minT = 0.5
    maxT = 4.01
    TStep = 0.1
    T = minT
    h = 0
    avem = 0.0
    Ts = []
    Ms = []
    avemsDic = {}

    for L in Ls:
        T = minT
        avems = []
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

            avem = quant.AveMPerSite(L, Ms)
            avems.append(avem)
            
            T += TStep
            T = round(T, 3)
        avemsDic[L] = avems
        
    return Ts, avemsDic, headerLines


def CreateAvemsLines(Ts, avemsDic, headerLines):
    avemLines = []
    
    header = "#" + "{0: >9}".format("T")
    for L in avemsDic:
        header += "{0: >30}".format("avem_L=" + str(L))

    headerLines.append("\n\n" + header + "\n\n")
    for headerLine in headerLines:
        avemLines.append(headerLine)

    for i in range(0, len(Ts)):
        avemLine = "{0: >10}".format(str(Ts[i]))
        for avems in avemsDic.values():
            avemLine += "{0: >30}".format(repr(avems[i]))
        avemLine += "\n"
        avemLines.append(avemLine)
    
    return avemLines


def CalculateAllAveMsPerSite():
    TQuantitiesDirPath = path.TQuantitiesDirPath
    #path.RecreateDir(TQuantitiesDirPath)
    TQuantitiesFileName = os.path.join(TQuantitiesDirPath, "avem" + path.dataFileExtension)
    Ts, avemsDic, headerLines = CalculateAllAvems(TQuantitiesDirPath)
    avemLines = CreateAvemsLines(Ts, avemsDic, headerLines)
    output.SaveLinesToFile(avemLines, TQuantitiesFileName)
    

CalculateAllAveMsPerSite()
