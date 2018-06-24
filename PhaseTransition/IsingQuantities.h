#pragma once

#include "IsingResults.h"
#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	class IsingQuantities
	{
	private:
		double siteFraction;
		double simStepsFraction;
		double sumH;
		double sumH2;
		double sumM;
		double sumM2;
		IsingMeantimeQuantities currentStepQuantities;
		bool quantitiesWasCalculatedInCurrentStep;
		double internalEnergy();
		double internalEnergy2();
		double specificHeat(double H, double H2, double T);
		double magnetization();
		double magnetization2();
		double megneticSusceptibility(double M, double M2, double T);
	public:
		IsingQuantities(int latticeSitesAmount, int simStepsAmount, IsingMeantimeQuantities& currentStepQuantities);
		~IsingQuantities();
		IsingMeantimeQuantities& getCurrentStepQuantities();
		void addCurrentStepQuantities(IsingMeantimeQuantities& quantities);
		void clearCurrentStepQuantities();
		bool wasQuantitiesCalculatedInCurrentStep();
		IsingResults* computeResults(double T);
	};
}