#include <iostream>
#include "Randomizer.h"


namespace PhaseTransition
{
	int Randomizer::randomNr(int max) const
	{
		return rand() % max;
	}

	double Randomizer::randomNrBetween0And1() const
	{
		return (double)rand() / (double)RAND_MAX;
	}

	double Randomizer::randomNr(double min, double max) const
	{
		return min + randomNrBetween0And1() * (max - min);
	}
}