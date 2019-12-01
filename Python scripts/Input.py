import os

maxFileSize = 1024 * 1024 * 250

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

def ReadEsAndMsWithHeader(quantitiesFilePath):
    if (os.path.getsize(quantitiesFilePath) > maxFileSize):
        return ReadMuchEsAndMsWithHeader(quantitiesFilePath)

    resultsLines = ReadFileLines(quantitiesFilePath)

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

def ReadMuchEsAndMsWithHeader(quantitiesFilePath):
    headerLines = []
    resultsArray = []
    EString = ""
    E = 0.0
    Es = []
    MString = ""
    M = 0.0
    Ms = []

    with open(quantitiesFilePath) as file:
        i = 0
        for line in file:
            if i < 5:
                headerLines.append(line)
            if i > 8:
                resultsArray = line.split()
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

def ReadTQuantityFk(resultsFilePath):
    resultsLines = ReadFileLines(resultsFilePath)

    resultsArray = []
    tString = ""
    t = 0
    ts = []
    EString = ""
    E = 0.0
    Es = []

    i = 0
    for resultsLine in resultsLines:
        if i > 8:
            resultsArray = resultsLine.split()
            tString = resultsArray[0]
            t = float(tString)
            EString = resultsArray[1]
            E = float(EString)
            ts.append(t)
            Es.append(E)
        i = 1 + i
    return ts, Es


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


def ReadSpins(spinsFilePath):
    spinsLines = ReadFileLines(spinsFilePath)

    headerLines = spinsLines[:6]
    L = 0.0
    T = 0.0
    for headerLine in headerLines:
        headerLine.rstrip()
        if headerLine.startswith("#L="):
            LString = headerLine.rstrip()[3:]
            L = int(LString)
        if headerLine.startswith("#T="):
            LString = headerLine.rstrip()[3:]
            T = float(LString)

    spinsLines = spinsLines[7:]
    spinsConfigs = []
    spinsConfig = []
    for spinsLine in spinsLines:
        spinsConfig = [int(i) for i in spinsLine.rstrip()]
        spinsConfigs.append(spinsConfig)

    return L, T, spinsConfigs


def ReadIons(ionsFilePath):
    ionsLines = ReadFileLines(ionsFilePath)
    ionsLines = ionsLines[8:]
    ionsConfigs = []
    for ionsLine in ionsLines:
        ionsConfig = [int(i) for i in ionsLine.rstrip()]
        ionsConfigs.append(ionsConfig)
    return ionsConfigs


# Read only one set of Ts with the assumption, that it is the same for each L
def ReadNeuronsActivities(activitiesFilePath):
    activitiesLines = ReadFileLines(activitiesFilePath)
    activitiesLines = activitiesLines[2:]
    Ts = []
    lowTActivitiesDic = dict()
    highTActivitiesDic = dict()
    L = 0
    for activitiesLine in activitiesLines:
        if activitiesLine.startswith("L="):
            LString = activitiesLine.rstrip()[2:]
            L = int(LString)
            lowTActivitiesDic[L] = []
            highTActivitiesDic[L] = []
        else:
            activitiesStrings = activitiesLine.split()
            if L == list(lowTActivitiesDic)[0]: # If actual L is the first key in a activities dict
                T = float(activitiesStrings[0])
                Ts.append(T)
            lowTActivity = float(activitiesStrings[1])
            highTActivity = float(activitiesStrings[2])
            lowTActivitiesDic[L].append(lowTActivity)
            highTActivitiesDic[L].append(highTActivity)
    return Ts, lowTActivitiesDic, highTActivitiesDic

# Read only one set of Ts with the assumption, that it is the same for each L
def ReadAccuracies(accuraciesFilePath):
    accuraciesLines = ReadFileLines(accuraciesFilePath)
    accuraciesLines = accuraciesLines[2:]
    Ts = []
    predictAccDic = dict()
    L = 0
    for accuraciesLine in accuraciesLines:
        if accuraciesLine.startswith("L="):
            LString = accuraciesLine.rstrip()[2:]
            L = int(LString)
            predictAccDic[L] = []
        else:
            accuracyStrings = accuraciesLine.split()
            if L == list(predictAccDic)[0]: # If actual L is the first key in a activities dict
                T = float(accuracyStrings[0])
                Ts.append(T)
            accuracy = float(accuracyStrings[1])
            predictAccDic[L].append(accuracy)
    return Ts, predictAccDic


def ReadAutocorrelations(autocorrelFilePath):
    autocorrelLines = ReadFileLines(autocorrelFilePath)
    headerLines = autocorrelLines[:5]
    L = 0
    for headerLine in headerLines:
        if headerLine.startswith("#L="):
            LString = headerLine.rstrip()[3:]
            L = int(LString)
            break
    
    autocorrelLines = autocorrelLines[9:]
    ts = list()
    EAutocorrels = list()
    MAutocorrels = list()
    for autocorrelLine in autocorrelLines:
        autocorrels = autocorrelLine.split()
        tString = autocorrels[0]
        t = int(tString)
        ts.append(t)
        EAutocorrelString = autocorrels[1]
        EAutocorrel = float(EAutocorrelString)
        EAutocorrels.append(EAutocorrel)
        MAutocorrelString = autocorrels[2]
        MAutocorrel = float(MAutocorrelString)
        MAutocorrels.append(MAutocorrel)

    return L, ts, EAutocorrels, MAutocorrels


def ReadAveDoSWithHeader(DoSFilePath):
    DoSLines = ReadFileLines(DoSFilePath)

    header = DoSLines[:5]

    Es = list()
    DoSes = list()

    EsLine = DoSLines[8]
    for EStr in EsLine.split():
        E = float(EStr)
        Es.append(E)

    EsAmount = len(Es)
    DoSLines = DoSLines[10:]
    for DoSLine in DoSLines:
        i = 0
        for DoSStr in DoSLine.split():
            DoS = float(DoSStr)
            if len(DoSes) < EsAmount:
                DoSes.append(DoS)
            else:
                DoSes[i] += DoS
            i += 1

    mcsAmount = len(DoSLines)
    i = 0
    for DoSSum in DoSes:
        DoSes[i] = DoSSum / mcsAmount
        i += 1
    
    return header, Es, DoSes