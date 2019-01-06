import os
import numpy as np
import Input as input
import AutocorrelationFunction as autocorrel
import Output as output
import Path as path

def CreateAutocorrelationLines(quantitiesFilePath):
    headerLines, Es, Ms = input.ReadEsAndMsWithHeader(quantitiesFilePath)

    if "Repeat" not in quantitiesFilePath:
        #Use only termalized data from
        print("Es length before cut:" + str(len(Es)))
        print("Ms length before cut:" + str(len(Ms)))
        Es = Es[50000:]
        Ms = Ms[50000:]
        print("Es length after cut:" + str(len(Es)))
        print("Ms length after cut:" + str(len(Ms)))

    ts = np.arange(1, 1000 + 1, 1)
    EAutocorrel = autocorrel.ComputeAutocorrelations(ts, Es)
    MAutocorrel = autocorrel.ComputeAutocorrelations(ts, Ms)
    
    autocorrelLines = []
    autocorrelLine = ""

    for headerLine in headerLines:
        autocorrelLines.append(headerLine)

    header = "#" + "{0: >9}".format("t") + "{0: >25}".format("EAutocorrel") + "{0: >25}".format("MAutocorrel") + "\n"
    autocorrelLines.append("\n\n" + header + "\n")

    tString = ""
    EAutocorrelString = ""
    MAutocorrelString = ""
    for i in range(0, len(ts)):
        tString = str(ts[i])
        EAutocorrelString = repr(EAutocorrel[i])
        MAutocorrelString = repr(MAutocorrel[i])
        autocorrelLine = "{0: >10}".format(tString) + "{0: >25}".format(EAutocorrelString) + "{0: >25}".format(MAutocorrelString) + "\n"
        autocorrelLines.append(autocorrelLine)

    return autocorrelLines

def CreateAutocorrelationFunctionFiles(quantitiesDirPath, autocorrelDirPath):
    autocorrelFileName = ""
    for quantitiesFileName in os.listdir(quantitiesDirPath):
        if quantitiesFileName.endswith(path.dataFileExtension):
            print(quantitiesFileName)
            quantitiesFilePath = os.path.join(quantitiesDirPath, quantitiesFileName)
            autocorrelFileName = quantitiesFileName.replace("Quantities", "Autocorrelations")
            autocorrelFilePath = os.path.join(autocorrelDirPath, autocorrelFileName)
            autocorrelLines = CreateAutocorrelationLines(quantitiesFilePath)
            output.SaveLinesToFile(autocorrelLines, autocorrelFilePath) 

def PreparePathsAndRunCalculations():
    quantitiesDirPath = path.quantitiesDirPath
    autocorrelDirPath = path.autocorrelDirPath
    path.RecreateDir(autocorrelDirPath)
    CreateAutocorrelationFunctionFiles(quantitiesDirPath, autocorrelDirPath)
    
PreparePathsAndRunCalculations()
