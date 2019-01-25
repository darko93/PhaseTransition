import numpy as np
import Math as math

# As - array of energies or megnetizations
# t - time interval for which autocorrelation function is being calculated
def AutocorrelationFunction(t, As):
    Ai = 0.0
    Aiplust = 0.0
    sumA = 0.0
    sumAiplust = 0.0
    sumAiAiplust = 0.0
    i = 0
    Alength = len(As)
    iplust = i + t
    iplustWithinRange = iplust < Alength

    while(iplustWithinRange):
        Ai = As[i]
        Aiplust = As[iplust]

        sumA += Ai
        sumAiAiplust += Ai * Aiplust
        sumAiplust += Aiplust

        i += 1
        iplust = i + t
        iplustWithinRange = iplust < Alength

    aveAiAiplust = sumAiAiplust / i
    aveAaveAiplust = (sumA * sumAiplust) / (i*i)

    autocorrelation = (aveAiAiplust - aveAaveAiplust)
    #autocorrelation = (aveAiAiplust - squaredAveA)

    return autocorrelation

# ts - time intervals for which autocorrelation function is being calculated
# As - array of energies or megnetizations
def ComputeAutocorrelations(ts, As):
    Aautocorrelations = []
    varA = math.Variance(As)
    for t in ts:
        print("t=" + str(t) + " ", end="")
        Atautocorrel = AutocorrelationFunction(t, As)
        Atautocorrel = Atautocorrel / varA # normalization
        Aautocorrelations.append(Atautocorrel)

    return Aautocorrelations