#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	IsingMeantimeQuantities::IsingMeantimeQuantities(double E, int M)
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

	int IsingMeantimeQuantities::getM() const
	{
		return this->M;
	}
}