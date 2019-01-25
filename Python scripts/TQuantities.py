def Variance(As):
    sumA = 0
    sumA2 = 0
    for A in As:
        sumA += A
        sumA2 += A * A
    AsAmount = len(As)
    aveA = sumA / AsAmount
    aveA2 = sumA2 / AsAmount
    variance = aveA2 - aveA * aveA
    return variance

def SpecificHeat(L, T, Es):
    kB = 1
    varE = Variance(Es)
    N = L * L
    Cv = varE / (N * kB * T * T)
    return Cv

def MagneticSusceptibility(L, T, Ms):
    kB = 1
    varM = Variance(Ms)
    N = L * L
    X = varM / (N * kB * T)
    return X

def AveMPerSite(L, Ms):
    N = L * L
    summ = 0
    for M in Ms:
        summ += abs(M) / N
    avem = summ / len(Ms)
    return avem

def BinderCumulant4(Ms):
    sumM2 = 0
    sumM4 = 0
    for M in Ms:
        M2 = M*M
        sumM2 += M2
        sumM4 += M2*M2
    MsAmount = len(Ms)
    aveM2 = sumM2 / MsAmount
    aveM4 = sumM4 / MsAmount
    binder = 1 - (aveM4 / (3 * aveM2 * aveM2))
    return binder