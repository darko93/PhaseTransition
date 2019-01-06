import numpy as np

# As - array of energies or megnetizations
# t - time interval for which autocorrelation function is being calculated
def AutocorrelationFunction(t, As):
    Ai = 0.0
    Aiplust = 0.0
    sumA = 0.0
    sumA2 = 0.0
    sumAiplust = 0.0
    sumAiAiplust = 0.0
    i = 0
    Alength = len(As)
    iplust = i + t
    iplustWithinRange = iplust < Alength

    while(iplustWithinRange):
        Ai = As[i]
        Aiplust = As[iplust]

        sumAiAiplust += Ai * Aiplust
        sumAiplust += Aiplust
        sumA += Ai
        sumA2 += Ai * Ai

        i += 1
        iplust = i + t
        iplustWithinRange = iplust < Alength

    aveAiAiplust = sumAiAiplust / i
    aveAaveAiplust = (sumA * sumAiplust) / (i*i)
    aveA = sumA / i
    aveA2 = sumA2 / i
    squaredAveA = aveA * aveA

    autocorrelation = (aveAiAiplust - aveAaveAiplust) / (aveA2 - squaredAveA)
    #autocorrelation = (aveAiAiplust - squaredAveA) / (aveA2 - squaredAveA)

    return autocorrelation

# ts - time intervals for which autocorrelation function is being calculated
# As - array of energies or megnetizations
def ComputeAutocorrelations(ts, As):
    Aautocorrelations = []
    for t in ts:
        Atautocorrel = AutocorrelationFunction(t, As)
        Aautocorrelations.append(Atautocorrel)

    return Aautocorrelations