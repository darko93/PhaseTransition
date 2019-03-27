import os
import Path as path

def RenameFiles(filesDirPath, oldName, newName):
    filePath = ""
    newFilePath = ""
    for fileName in os.listdir(filesDirPath):
        if fileName.endswith(path.dataFileExtension):
            filePath = os.path.join(filesDirPath, fileName)
            newFilePath = filePath.replace(oldName, newName)
            os.rename(filePath, newFilePath)

RenameFiles("E:\\Ising2\\IsingSpins", ".dat", "_2.dat")