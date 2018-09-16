#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	IsingMeantimeQuantities::IsingMeantimeQuantities(double H, int M)
		: H(H), M(M)
	{
	}

	IsingMeantimeQuantities::~IsingMeantimeQuantities()
	{
	}

	IsingMeantimeQuantities IsingMeantimeQuantities::zeroes()
	{
		return IsingMeantimeQuantities(0.0, 0);
	}

	double IsingMeantimeQuantities::getH() const
	{
		return this->H;
	}

	int IsingMeantimeQuantities::getM() const
	{
		return this->M;
	}
}