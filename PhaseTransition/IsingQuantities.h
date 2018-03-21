#pragma once

#include "IsingResults.h"

namespace PhaseTransition
{
	class IsingQuantities
	{
		friend class IsingModel;
	private:
		double siteFraction;

		double PartitionFunction; // sum over states [exp(-H/T)]
		double HExpMinusBetaH; // sum over states [H * exp(-H/T)]
		double H2ExpMinusBetaH; // sum over states [H^2 * exp(-H/T)]
		double MExpMinusBetaH; // sum over states [M * exp(-beta*H)] // beta = 1/T
		double M2ExpMinusBetaH; // sum over states [M^2 * exp(-beta*H)]
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