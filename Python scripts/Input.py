def ReadFileLines(filePath):
    fileLines = []
    with open(filePath) as file:
        fileLines = file.readlines()
    return fileLines

def ReadEs(quantitiesFilePath):
    quantitiesLines = ReadFileLines(quantitiesFilePath)

    resultsArray = []
    EString = ""
    E = 0.0
    Es = []

    i = 0
    for resultsLine in quantitiesLines:
        if i > 8:
            resultsArray = resultsLine.split()
            EString = resultsArray[1]
            E = float(EString)
            Es.append(E)
        i = 1 + i

    return Es

def ReadMs(quantitiesFilePath):
    quantitiesLines = ReadFileLines(quantitiesFilePath)

    resultsArray = []
    MString = ""
    M = 0.0
    Ms = []

    i = 0
    for resultsLine in quantitiesLines:
        if i > 8:
            resultsArray = resultsLine.split()
            MString = resultsArray[2]
            M = float(MString)
            Ms.append(M)
        i = 1 + i

    return Ms

def ReadEsAndMs(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    resultsArray = []
    EString = ""
    E = 0.0
    Es = []
    MString = ""
    M = 0.0
    Ms = []

    i = 0
    for resultsLine in resultsLines:
        if i > 8:
            resultsArray = resultsLine.split()
            EString = resultsArray[1]
            E = float(EString)
            MString = resultsArray[2]
            M = float(MString)
            Es.append(E)
            Ms.append(M)
        i = 1 + i

    return Es, Ms

def ReadEsAndMsWithHeader(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    headerLines = []
    resultsArray = []
    EString = ""
    E = 0.0
    Es = []
    MString = ""
    M = 0.0
    Ms = []

    i = 0
    for resultsLine in resultsLines:
        if i < 5:
            headerLines.append(resultsLine)
        if i > 8:
            resultsArray = resultsLine.split()
            EString = resultsArray[1]
            E = float(EString)
            MString = resultsArray[2]
            M = float(MString)
            Es.append(E)
            Ms.append(M)
        i = 1 + i

    return headerLines, Es, Ms

def ReadEsWithHeader(quantitiesFilePath):
    resultsLines = ReadFileLines(quantitiesFilePath)

    headerLines = []
    resultsArray = []
    EString = ""
    E = 0.0
    Es = []

    i = 0
    for resultsLine in resultsLines:
        if i < 5:
            headerLines.append(resultsLine)
        if i > 8:
            resultsArray = resultsLine.split()
            EString = resultsArray[1]
            E = float(EString)
            Es.append(E)
        i = 1 + i

    return headerLines, Es

def ReadMsWithHeader(quantitiesFilePath):
    resultsLines = ReadFileLines(quantitiesFilePath)

    headerLines = []
    resultsArray = []
    MString = ""
    M = 0.0
    Ms = []

    i = 0
    for resultsLine in resultsLines:
        if i < 5:
            headerLines.append(resultsLine)
        if i > 8:
            resultsArray = resultsLine.split()
            MString = resultsArray[2]
            M = float(MString)
            Ms.append(M)
        i = 1 + i

    return headerLines, Ms

def ReadtsAndEsAndMs(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    resultsArray = []
    tString = ""
    t = 0
    ts = []
    EString = ""
    E = 0.0
    Es = []
    MString = ""
    M = 0.0
    Ms = []

    i = 0
    for resultsLine in resultsLines:
        if i > 8:
            resultsArray = resultsLine.split()
            tString = resultsArray[0]
            t = int(tString)
            EString = resultsArray[1]
            E = float(EString)
            MString = resultsArray[2]
            M = float(MString)
            ts.append(t)
            Es.append(E)
            Ms.append(M)
        i = 1 + i
    return ts, Es, Ms

