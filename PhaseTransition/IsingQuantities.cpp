#include "IsingQuantities.h"

namespace PhaseTransition
{
	IsingQuantities::IsingQuantities(int latticeSitesAmount)
		: SumExpMinusBetaH(0.0), SumHExpMinusBetaH(0.0), SumH2ExpMinusBetaH(0.0), SumMExpMinusBetaH(0.0), SumM2ExpMinusBetaH(0.0)
	{
		this->siteFraction = 1.0 / latticeSitesAmount;
	}

	IsingQuantities::~IsingQuantities()
	{
	}

	double IsingQuantities::internalEnergy()
	{
		return this->siteFraction * this->SumHExpMinusBetaH / this->SumExpMinusBetaH; // U = <H> = 1/N * [sum(H*exp(-beta*H))] / [sum(exp(-beta*H))] // sum over states
	}

	double IsingQuantities::internalEnergy2()
	{
		return this->siteFraction * this->SumH2ExpMinusBetaH / this->SumExpMinusBetaH; // U2 = <H^2> = 1/N * [sum(H^2 * exp(-beta*H))] / [sum(exp(-beta*H))]
	}

	double IsingQuantities::specificHeat(double U, double U2, double T)
	{
		return this->siteFraction * (U2 - U * U) / (T*T); // 1/N * (<H^2> - <H>^2) / T^2
	}

	double IsingQuantities::megneticSusceptibility(double T)
	{
		double aveM = this->siteFraction * (this->SumMExpMinusBetaH / this->SumExpMinusBetaH); // <M> = 1/N * (sum[M*exp(-beta*H)] / sum[exp(-beta*H)])
		double aveM2 = this->siteFraction * (this->SumM2ExpMinusBetaH / this->SumExpMinusBetaH); // <M^2> = 1/N * (sum[M^2*exp(-beta*H)] / sum[exp(-beta*H)])
		return this->siteFraction * (aveM2 - aveM * aveM) / (T); // X = 1/N * (<M^2> - <M>^2) / T
	}

	IsingResults* IsingQuantities::computePartOfResults(double T)
	{
		double U = internalEnergy();
		double U2 = internalEnergy2();
		double Cv = specificHeat(U, U2, T);
		double X = megneticSusceptibility(T);
		IsingResults* results = new IsingResults(T, U, Cv, X);
		return results;
	}
}
