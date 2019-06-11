class FkSimulationParameters:

    dE = 0.0
    gamma = 0.0
    kB = 1.0
    t = 1.0
    mu = 0.0
    mcsAmount = 1
    L = 0
    N = 0
    U = 0.0
    T = 0.0
    beta = 0.0
    saveMeantimeQuantities = False
    saveIonicConfig = False
    savingIonicConfigMcsInterval = 1

    def setL(self, L):
        self.L = L
        self.N = L*L

    def setT(self, T):
        self.T = T
        self.beta = 1 / (self.kB * T)