#include <climits>
#include "Randomizer.h"


namespace PhaseTransition
{
	Randomizer::Randomizer() : mt(std::random_device()()), realDist(std::uniform_real_distribution<double>(0.0, 1.0)),
		intDist(std::uniform_int_distribution<int>(0, INT_MAX))
	{
		std::random_device device;
		// Call device() twice, because it returns 32 bit unsigned int and we want 64 bit seed
		// https://stackoverflow.com/questions/24334012/best-way-to-seed-mt19937-64-for-monte-carlo-simulations
		unsigned long long seed = (static_cast<uint64_t>(device()) << 32) | device();
		mt.seed(seed);
	}

	void Randomizer::setMaxRandomIntNr(int max)
	{
		this->intDist = std::uniform_int_distribution<int>(0, max);
	}

	int Randomizer::randomIntNr()
	{
		int randomNr = this->intDist(this->mt);
		return randomNr;
	}

	double Randomizer::randomNrBetween0And1()
	{
		double randomNr = this->realDist(this->mt);
		return randomNr;
	}
}