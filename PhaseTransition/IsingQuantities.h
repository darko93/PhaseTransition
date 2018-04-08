#pragma once

#include "IsingResults.h"

namespace PhaseTransition
{
	class IsingQuantities
	{
		friend class IsingModel;
	private:
		double siteFraction;
		double simStepsFraction;
		double sumH;
		double sumH2;
		double sumM;
		double sumM2;
	public:
		IsingQuantities(int latticeSitesAmount, int simStepsAmount);
		~IsingQuantities();
		double internalEnergy();
		double internalEnergy2();
		double specificHeat(double H, double H2, double T);
		double magnetization();
		double magnetization2();
		double megneticSusceptibility(double M, double M2, double T);
		IsingResults* computeResults(double T);
	};
}