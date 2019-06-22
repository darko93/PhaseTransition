class FkSimulationParameters:

    saveMeantimeQuantities = False
    saveDoS = False
    saveIons = False
    savingIonsMcsInterval = 1
    reuseIons = False
    repeat = 1
    dE = 0.0
    gamma = 0.0
    kB = 1.0
    t = 1.0
    mu = 0.0
    elConc = 0.0
    mcsAmount = 1
    L = 0
    N = 0
    NFactor = 0.0
    U = 0.0
    T = 0.0
    beta = 0.0

    def setL(self, L):
        self.L = L
        self.N = L*L
        self.NFactor = 1.0 / self.N

    def setT(self, T):
        self.T = T
        self.beta = 1 / (self.kB * T)