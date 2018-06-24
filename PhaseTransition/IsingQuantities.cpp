#include "IsingQuantities.h"

namespace PhaseTransition
{
	IsingQuantities::IsingQuantities(int latticeSitesAmount, int simStepsAmount, IsingMeantimeQuantities& currentStepQuantities)
		: sumH(0.0), sumH2(0.0), sumM(0.0), sumM2(0.0), currentStepQuantities(currentStepQuantities)
	{
		this->siteFraction = 1.0 / latticeSitesAmount;
		this->simStepsFraction = 1.0 / simStepsAmount;
	}

	IsingQuantities::~IsingQuantities()
	{
	}

	IsingMeantimeQuantities& IsingQuantities::getCurrentStepQuantities()
	{
		return this->currentStepQuantities;
	}

	void IsingQuantities::addCurrentStepQuantities(IsingMeantimeQuantities& quantities)
	{
		this->currentStepQuantities = quantities;
		this->quantitiesWasCalculatedInCurrentStep = true;
		this->sumH += quantities.getH();
		this->sumH2 += quantities.getH2();
		this->sumM += quantities.getM();
		this->sumM2 += quantities.getM2();
	}

	void IsingQuantities::clearCurrentStepQuantities()
	{
		this->quantitiesWasCalculatedInCurrentStep = false;
	}

	bool IsingQuantities::wasQuantitiesCalculatedInCurrentStep()
	{
		return this->quantitiesWasCalculatedInCurrentStep;
	}

	double IsingQuantities::internalEnergy()
	{
		return this->siteFraction * this->simStepsFraction * this->sumH;
	}

	double IsingQuantities::internalEnergy2()
	{
		return this->siteFraction * this->simStepsFraction * this->sumH2;
	}

	double IsingQuantities::specificHeat(double U, double U2, double T)
	{
		return this->siteFraction * (U2 - U * U) / (T*T); // 1/N * (<H^2> - <H>^2) / T^2
	}

	double IsingQuantities::magnetization()
	{
		return this->siteFraction * this->simStepsFraction * this->sumM;
	}

	double IsingQuantities::magnetization2()
	{
		return this->siteFraction * this->simStepsFraction * this->sumM2;
	}

	double IsingQuantities::megneticSusceptibility(double M, double M2, double T)
	{
		return this->siteFraction * (M2 - M * M) / (T);
	}

	IsingResults* IsingQuantities::computeResults(double T)
	{
		double U = internalEnergy();
		double U2 = internalEnergy2();
		double Cv = specificHeat(U, U2, T);
		double M = magnetization();
		double M2 = magnetization2();
		double X = megneticSusceptibility(M, M2, T);

		IsingResults* results = new IsingResults(T, U, Cv, M, X);
		return results;
	}
}
