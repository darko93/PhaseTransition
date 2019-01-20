#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	IsingMeantimeQuantities::IsingMeantimeQuantities(int E, int M)
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

	int IsingMeantimeQuantities::getE() const
	{
		return this->E;
	}

	int IsingMeantimeQuantities::getM() const
	{
		return this->M;
	}
}