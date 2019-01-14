import os
import Path as path
import Input as input
import Output as output
import Quantities as quant


def GetQuantitiesFilePath(L, T, h):
    quantitiesFileName = "Quantities_L=" + str(L) + "_T=" + "{0:.3f}".format(T) + "_h=" + "{0:.3f}".format(h) + path.dataFileExtension
    quantitiesFilePath = os.path.join(path.quantitiesDirPath, quantitiesFileName)
    return quantitiesFilePath


def CalculateAllCvs(TQuantitiesDirPath):
    Ls = [10, 20, 30, 40, 50]
    minT = 2.269 #0.5
    maxT = 2.269 #4.01
    TStep = 0.1
    T = minT
    h = 0
    Cv = 0.0
    Ts = []
    Es = []
    CvsDic = {}

    for L in Ls:
        T = minT
        Cvs = []
        while (T <= maxT):
            quantitiesFilePath = GetQuantitiesFilePath(L, T, h)
            print(quantitiesFilePath)

            firstL = L == Ls[0]
            if firstL:
                Ts.append(T)

            if firstL and T == minT:
                # Read header only from the first data file
                headerLines, Es = input.ReadEsWithHeader(quantitiesFilePath)
            else:
                Es = input.ReadEs(quantitiesFilePath)

            if "Repeat" not in quantitiesFilePath:
                #Use only termalized data
                print("Es length before cut:" + str(len(Es)))
                Es = Es[50000:]
                print("Es length after cut:" + str(len(Es)))

            Cv = quant.SpecificHeat(L, T, Es)
            Cvs.append(Cv)
            
            T += TStep
            T = round(T, 3)
        CvsDic[L] = Cvs
        
    return Ts, CvsDic, headerLines


def CreateCvsLines(Ts, CvsDic, headerLines):
    CvLines = []
    
    header = "#" + "{0: >9}".format("T")
    for L in CvsDic:
        header += "{0: >30}".format("Cv_L=" + str(L))

    headerLines.append("\n\n" + header + "\n\n")
    for headerLine in headerLines:
        CvLines.append(headerLine)

    for i in range(0, len(Ts)):
        CvLine = "{0: >10}".format(str(Ts[i]))
        for Cvs in CvsDic.values():
            CvLine += "{0: >30}".format(repr(Cvs[i]))
        CvLine += "\n"
        CvLines.append(CvLine)
    
    return CvLines


def CalculateAllSpecificHeats():
    TQuantitiesDirPath = path.TQuantitiesDirPath
    #path.RecreateDir(TQuantitiesDirPath)
    TQuantitiesFileName = os.path.join(TQuantitiesDirPath, "Cv" + path.dataFileExtension)
    Ts, CvsDic, headerLines = CalculateAllCvs(TQuantitiesDirPath)
    CvLines = CreateCvsLines(Ts, CvsDic, headerLines)
    output.SaveLinesToFile(CvLines, TQuantitiesFileName)
    

CalculateAllSpecificHeats()