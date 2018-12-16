#include <random>
#include <climits>
#include "Randomizer.h"


namespace PhaseTransition
{
	Randomizer::Randomizer() : mt(std::random_device()()), realDist(std::uniform_real_distribution<double>(0.0, 1.0)),
		intDist(std::uniform_int_distribution<int>(0, INT_MAX))
	{
	}

	void Randomizer::setMaxRandomIntNr(int max)
	{
		this->intDist = std::uniform_int_distribution<int>(0, max);
	}

	int Randomizer::randomIntNr() const
	{
		int randomNr = this->intDist(this->mt);
		return randomNr;
	}

	double Randomizer::randomNrBetween0And1() const
	{
		double randomNr = this->realDist(this->mt);
		return randomNr;
	}
}