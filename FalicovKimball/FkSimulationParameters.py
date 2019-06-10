class FkSimulationParameters:

    kB = 1
    N = 0
    beta = 0.0

    def __init__(self, dE, gamma, t, mu, mcsAmount, L, U, T):
        self.dE = dE
        self.gamma = gamma
        self.t = t
        self.mu = mu
        self.mcsAmount = mcsAmount
        self.setL(L)
        self.U = U
        self.setT(T)

    def setL(self, L):
        self.L = L
        self.N = L*L

    def setT(self, T):
        self.T = T
        self.beta = 1 / (self.kB * T)