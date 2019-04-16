import os
import shutil

resultsDirPath = os.path.join("E:", os.sep, "Dadeś", "3 mln", "C++")
# resultsDirPath = os.path.join("C:", os.sep, "Users", "Darko", "Desktop", "4 8 16 32", "Nowy generator")
quantitiesDirName = "IsingQuantities"
autocorrelDirName = "IsingAutocorrelations"
TQuantitiesDirName = "IsingTQuantities"
quantitiesDirPath = os.path.join(resultsDirPath, quantitiesDirName)
autocorrelDirPath = os.path.join(resultsDirPath, autocorrelDirName)
TQuantitiesDirPath = os.path.join(resultsDirPath, TQuantitiesDirName)
spinsDirPath = os.path.join("D:", os.sep)
spinsDirName = "Spiny"
spinsDirPath = os.path.join(spinsDirPath, spinsDirName)
dataFileExtension = ".dat"
activitiesFilePath = "D:\\activities" + dataFileExtension
predictAccsFilePath = "D:\\accuracies" + dataFileExtension


def RecreateDir(dirPath):
    if os.path.exists(dirPath):
        shutil.rmtree(dirPath)
    os.mkdir(dirPath)