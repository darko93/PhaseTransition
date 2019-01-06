import numpy as np
import AutocorrelationFunction as autocorrel
import Input as input

ts = np.arange(1, 1000 + 1, 10)
Es, Ms = input.ReadEsAndMs("IsingQuantities/Quantities_L=50_T=2.20_h=0.00.dat")
EAutocorrel = autocorrel.ComputeAutocorrelations(ts, Es)