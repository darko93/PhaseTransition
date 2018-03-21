#include <iostream>
#include "Randomizer.h"


namespace PhaseTransition
{
	double Randomizer::randomNrBetween0And1()
	{
		return (double)rand() / (double)RAND_MAX;
	}

	double Randomizer::randomNr(double min, double max)
	{
		return min + randomNrBetween0And1() * (max - min);
	}
}