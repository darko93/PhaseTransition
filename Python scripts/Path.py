import os
import shutil

# resultsDirPath = os.path.join("E:", os.sep, "Darek", "30 mln", "C++", "10-30")
# quantitiesDirName = "IsingQuantities10"
# autocorrelDirName = "IsingAutocorrelations"
# TQuantitiesDirName = "IsingTQuantities"

resultsDirPath = os.path.join("D:", os.sep, "Darko", "Programowanie", "Symulacje", "PhaseTransition", "FalicovKimball")
quantitiesDirName = "FkQuantities"
autocorrelDirName = "IsingAutocorrelations"
TQuantitiesDirName = "FkTQuantities"

quantitiesDirPath = os.path.join(resultsDirPath, quantitiesDirName)
autocorrelDirPath = os.path.join(resultsDirPath, autocorrelDirName)
TQuantitiesDirPath = os.path.join(resultsDirPath, TQuantitiesDirName)
spinsDirPath = os.path.join("D:", os.sep)
spinsDirName = "SpinyDuzo"
spinsDirPath = os.path.join(spinsDirPath, spinsDirName)
dataFileExtension = ".dat"
activitiesFilePath = "D:\\activities" + dataFileExtension
predictAccsFilePath = "D:\\accuracies" + dataFileExtension


def RecreateDir(dirPath):
    if os.path.exists(dirPath):
        shutil.rmtree(dirPath)
    os.mkdir(dirPath)