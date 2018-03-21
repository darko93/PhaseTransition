#include "IsingQuantities.h"

namespace PhaseTransition
{
	IsingQuantities::IsingQuantities(int latticeSitesAmount)
		: PartitionFunction(0.0), HExpMinusBetaH(0.0), H2ExpMinusBetaH(0.0), MExpMinusBetaH(0.0), M2ExpMinusBetaH(0.0)
	{
		this->siteFraction = 1.0 / latticeSitesAmount;
	}

	IsingQuantities::~IsingQuantities()
	{
	}

	double IsingQuantities::internalEnergy()
	{
		return this->siteFraction * this->HExpMinusBetaH / this->PartitionFunction; // U = <H> = 1/N * [sum(H*exp(-beta*H))] / [sum(exp(-beta*H))] // sum over states
	}

	double IsingQuantities::internalEnergy2()
	{
		return this->siteFraction * this->H2ExpMinusBetaH / this->PartitionFunction; // U2 = <H^2> = 1/N * [sum(H^2 * exp(-beta*H))] / [sum(exp(-beta*H))]
	}

	double IsingQuantities::specificHeat(double U, double U2, double T)
	{
		return this->siteFraction * (U2 - U * U) / (T*T); // 1/N * (<H^2> - <H>^2) / (kB*T)^2
	}

	double IsingQuantities::megneticSusceptibility(double T)
	{
		double aveM = this->siteFraction * (this->MExpMinusBetaH / this->PartitionFunction); // <M> = 1/N * (sum[M*exp(-beta*H)] / sum[exp(-beta*H)])
		double aveM2 = this->siteFraction * (this->M2ExpMinusBetaH / this->PartitionFunction); // <M^2> = 1/N * (sum[M^2*exp(-beta*H)] / sum[exp(-beta*H)])
		return this->siteFraction * (aveM2 - aveM * aveM) / (T); // X = 1/N * (<M^2> - <M>^2) / (kB*T)
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
