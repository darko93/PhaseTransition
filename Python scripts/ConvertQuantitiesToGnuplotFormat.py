import os
import shutil
import Input as input
import Output as output
import Path as path

def ConvertToGnuplotFormat(quantitiesLines):
    newQuantitiesLines = []
    iQuantitiesLine = ""
    charsList = []
    for i in range(0, len(quantitiesLines)):
        iQuantitiesLine = quantitiesLines[i]
        if i < 5:
            iQuantitiesLine = "#" + iQuantitiesLine
        elif i == 7:
            charsList = list(iQuantitiesLine)
            charsList[0] = "#"
            iQuantitiesLine = "".join(charsList)
        newQuantitiesLines.append(iQuantitiesLine)
    return newQuantitiesLines

def ConvertQuantitiesToGnuplotFormat(quantitiesDirPath, newQuantitiesDirPath):
    newQuantitiesFilePath = ""
    for quantitiesFileName in os.listdir(quantitiesDirPath):
        if quantitiesFileName.endswith(path.dataFileExtension):
            quantitiesFilePath = os.path.join(quantitiesDirPath, quantitiesFileName)
            newQuantitiesFilePath = os.path.join(newQuantitiesDirPath, quantitiesFileName)
            quantitiesLines = input.ReadFileLines(quantitiesFilePath)
            newQuantitiesLines = ConvertToGnuplotFormat(quantitiesLines)
            output.SaveLinesToFile(newQuantitiesLines, newQuantitiesFilePath) 

def PreparePathsAndRunConversion():
    resultsDirPath = path.resultsDirPath
    quantitiesDirPath = path.quantitiesDirPath
    newQuantitiesDirPath = os.path.join(resultsDirPath, "ConvertedIsingQuantities")
    path.RecreateDir(newQuantitiesDirPath)
    ConvertQuantitiesToGnuplotFormat(quantitiesDirPath, newQuantitiesDirPath)

PreparePathsAndRunConversion()