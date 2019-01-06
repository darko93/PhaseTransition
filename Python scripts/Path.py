import os
import shutil

#C:\Users\Darko\Desktop\4 8 16 32\Fortran\IsingQuantities

resultsDirPath = os.path.join("C:", os.sep, "Users", "Darko", "Desktop", "4 8 16 32", "Nowy generator dużo")
quantitiesDirName = "IsingQuantities"
autocorrelDirName = "IsingAutocorrelations"
quantitiesDirPath = os.path.join(resultsDirPath, quantitiesDirName)
autocorrelDirPath = os.path.join(resultsDirPath, autocorrelDirName)
dataFileExtension = ".dat"

def RecreateDir(dirPath):
    if os.path.exists(dirPath):
        shutil.rmtree(dirPath)
    os.mkdir(dirPath)