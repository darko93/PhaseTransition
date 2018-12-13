#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	IsingMeantimeQuantities::IsingMeantimeQuantities(double E, double M)
		: E(E), M(M)
	{
	}

	IsingMeantimeQuantities::~IsingMeantimeQuantities()
	{
	}

	IsingMeantimeQuantities IsingMeantimeQuantities::zeroes()
	{
		return IsingMeantimeQuantities(0.0, 0);
	}

	double IsingMeantimeQuantities::getE() const
	{
		return this->E;
	}

	double IsingMeantimeQuantities::getM() const
	{
		return this->M;
	}
}