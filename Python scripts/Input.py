def ReadFileLines(filePath):
    fileLines = []
    with open(filePath) as file:
        fileLines = file.readlines()
    return fileLines

def Read2ndAnd3rdColumns(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    Ys = []
    Zs = []

    YString = ""
    ZString = ""
    Y = 0.0
    Z = 0.0

    i = 0
    for resultsLine in resultsLines:
        if i > 8:
            resultsArray = resultsLine.split()
            YString = resultsArray[1]
            Y = float(YString)
            ZString = resultsArray[2]
            Z = float(ZString)
            Ys.append(Y)
            Zs.append(Z)
        i = 1 + i

    return Ys, Zs

def ReadThreeColumns(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    Xs = []
    Ys = []
    Zs = []

    XString = ""
    YString = ""
    ZString = ""
    X = 0.0
    Y = 0.0
    Z = 0.0

    i = 0
    for resultsLine in resultsLines:
        if i > 8:
            resultsArray = resultsLine.split()
            XString = resultsArray[0]
            X = int(XString)
            YString = resultsArray[1]
            Y = float(YString)
            ZString = resultsArray[2]
            Z = float(ZString)
            Xs.append(X)
            Ys.append(Y)
            Zs.append(Z)
        i = 1 + i

    return Xs, Ys, Zs

def ReadEsAndMs(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    Es = []
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
    Es = []
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

def ReadtsAndEsAndMs(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    ts = []
    Es = []
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

