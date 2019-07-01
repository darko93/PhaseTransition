import os
import Path as path
import Input as input
import Output as output

def CreateAveDoSLines(DoSFilePath):
    header, Es, aveDoSes = input.ReadAveDoSWithHeader(DoSFilePath)

    aveDoSLines = list()
    aveDoSLines.extend(header)
    aveDoSLines.append("\n\n#E\tDoS(E)\n")
    for i in range(len(Es)):
        aveDoSLine = "\n{0} {1}".format(Es[i], aveDoSes[i])
        aveDoSLines.append(aveDoSLine)
    
    return aveDoSLines


def AveDoS():

    DoSDirPath = path.DoSDirPath
    
    for DoSFileName in os.listdir(DoSDirPath):
        if DoSFileName.endswith(path.dataFileExtension):
            DoSFilePath = os.path.join(DoSDirPath, DoSFileName)
            aveDoSFileName = DoSFileName.replace("DoS", "AveDoS")
            aveDoSFilePath = os.path.join(DoSDirPath, aveDoSFileName)
            aveDoSLines = CreateAveDoSLines(DoSFilePath)
            output.SaveLinesToFile(aveDoSLines, aveDoSFilePath) 


AveDoS()