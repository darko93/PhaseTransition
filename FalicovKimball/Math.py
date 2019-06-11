import random

class Math:

    @staticmethod
    def getRandomIndices(total, amount):
        possibleIndices = list()
        for i in range(total):
            possibleIndices.append(i)
        randomIndices = random.sample(possibleIndices, k=amount)
        return randomIndices

N = 10
halfN = int(0.5*N)
print(Math.getRandomIndices(N, halfN))