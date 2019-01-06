import os
import shutil
import Input as input
import Output as output
import Path as path

def TotalMagnetizationsToMagnetizationsPerSite(resultsLines):
    latticeSitesAmount = 0
    resultsArray = []
    MString = ""
    M = 0.0
    newResultsLines = []
    newResultsLine = ""
        
    i = 0
    for resultsLine in resultsLines:
        if i == 4:
            newResultsLines.append(resultsLine)
            resultsLine = resultsLine.rstrip()
            LString = resultsLine[12:]
            L = int(LString)
            latticeSitesAmount = L * L
        elif i == 7:
            newResultsLine = resultsLine.replace("H", "E")
            newResultsLines.append(newResultsLine)
        elif i > 8:
            resultsArray = resultsLine.split()
            MString = resultsArray[2]
            M = float(MString)
            M = M / latticeSitesAmount
            MString = "{:.4f}".format(M)
            newResultsLine = "{0: >10}".format(resultsArray[0]) + "{0: >25}".format(resultsArray[1]) + "{0: >25}".format(MString) + "\n"
            newResultsLines.append(newResultsLine)
        else:
            newResultsLines.append(resultsLine)
        i = i + 1
    return newResultsLines

def CreateNewResultsFile(resultsFilePath, newResultsDirPath):
    resultsLines = input.ReadFileLines(resultsFilePath)

    newResultsLines = TotalMagnetizationsToMagnetizationsPerSite(resultsLines)
    resultsFileName = os.path.basename(resultsFilePath)
    resultsFileNameWithoutExtension = os.path.splitext(resultsFileName)[0]
    newResultsFileName = resultsFileNameWithoutExtension + path.dataFileExtension
    newResultsFilePath = os.path.join(newResultsDirPath, newResultsFileName)
    output.SaveLinesToFile(newResultsLines, newResultsFilePath)

def CreateNewResultsFiles(resultsDirPath, newResultsDirPath):
    for resultsFileName in os.listdir(resultsDirPath):
        if resultsFileName.endswith(path.dataFileExtension):
            resultsFilePath = os.path.join(resultsDirPath, resultsFileName)
            CreateNewResultsFile(resultsFilePath, newResultsDirPath) 

def PreparePathsAndRunCalculations():
    resultsDirPath = path.resultsDirPath
    oldResultsDirPath = path.quantitiesDirPath
    newResultsDirPath = os.path.join(resultsDirPath, "RecalculatedMagnetizations")
    if os.path.exists(newResultsDirPath):
        shutil.rmtree(newResultsDirPath)
    os.mkdir(newResultsDirPath)
    CreateNewResultsFiles(oldResultsDirPath, newResultsDirPath)

PreparePathsAndRunCalculations()
