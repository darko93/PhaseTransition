#pragma once

#include "IsingResults.h"

namespace PhaseTransition
{
	class IsingQuantities
	{
		friend class IsingModel;
	private:
		double siteFraction;

		double SumExpMinusBetaH; // sum over states [exp(-H/T)]
		double SumHExpMinusBetaH; // sum over states [H * exp(-H/T)]
		double SumH2ExpMinusBetaH; // sum over states [H^2 * exp(-H/T)]
		double SumMExpMinusBetaH; // sum over states [M * exp(-beta*H)] // beta = 1/T
		double SumM2ExpMinusBetaH; // sum over states [M^2 * exp(-beta*H)]
	public:
		IsingQuantities(int latticeSitesAmount);
		~IsingQuantities();
		double internalEnergy();
		double internalEnergy2();
		double specificHeat(double H, double H2, double T);
		double megneticSusceptibility(double T);
		IsingResults* computePartOfResults(double T);
	};
}