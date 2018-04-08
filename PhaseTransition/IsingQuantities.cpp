#include "IsingQuantities.h"

namespace PhaseTransition
{
	IsingQuantities::IsingQuantities(int latticeSitesAmount, int simStepsAmount)
		: SumExpMinusBetaH(0.0), SumHExpMinusBetaH(0.0), SumH2ExpMinusBetaH(0.0), SumMExpMinusBetaH(0.0), SumM2ExpMinusBetaH(0.0)
	{
		this->siteFraction = 1.0 / latticeSitesAmount;
		this->simStepsFraction = 1.0 / simStepsAmount;
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

	double IsingQuantities::aveH()
	{
		return this->simStepsFraction * this->sumH;
	}

	double IsingQuantities::aveH2()
	{
		return this->simStepsFraction * this->sumH2;
	}

	double IsingQuantities::aveM()
	{
		return this->simStepsFraction * this->sumM;
	}

	double IsingQuantities::aveM2()
	{
		return this->simStepsFraction * this->sumM2;
	}

	double IsingQuantities::aveCv(double aveH, double aveH2, double T)
	{
		return this->siteFraction * (aveH2 - aveH*aveH) / (T*T);
	}

	double IsingQuantities::aveX(double aveM, double aveM2, double T)
	{
		return this->siteFraction * (aveM2 - aveM * aveM) / (T); // X = 1/N * (<M^2> - <M>^2) / T
	}

	IsingResults* IsingQuantities::computePartOfResults(double T)
	{
		double U = internalEnergy();
		double U2 = internalEnergy2();
		double Cv = specificHeat(U, U2, T);
		double X = megneticSusceptibility(T);

		double ave_H = aveH();
		double ave_H2 = aveH2();
		double ave_M = aveM();
		double ave_M2 = aveM2();
		double ave_Cv = aveCv(ave_H, ave_H2, T);
		double ave_X = aveX(ave_M, ave_M2, T);

		double ave_H_PerSite = this->siteFraction * ave_H;
		double ave_M_PerSite = this->siteFraction * ave_M;

		double aveMExp = this->siteFraction * (this->SumMExpMinusBetaH / this->SumExpMinusBetaH);

		IsingResults* results = new IsingResults(T, U, Cv, X, ave_H_PerSite, ave_Cv, ave_M_PerSite, ave_X, aveMExp);
		return results;
	}
}
