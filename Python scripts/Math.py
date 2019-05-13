import scipy

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