#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	IsingMeantimeQuantities::IsingMeantimeQuantities(double T, double H, int M)
		: T(T), H(H), M(M)
	{
	}

	IsingMeantimeQuantities::~IsingMeantimeQuantities()
	{
	}

	IsingMeantimeQuantities IsingMeantimeQuantities::zeroes()
	{
		return IsingMeantimeQuantities(0.0, 0.0, 0.0);
	}

	double PhaseTransition::IsingMeantimeQuantities::getT()
	{
		return this->T;
	}

	double IsingMeantimeQuantities::getH()
	{
		return this->H;
	}

	int IsingMeantimeQuantities::getM()
	{
		return this->M;
	}
}