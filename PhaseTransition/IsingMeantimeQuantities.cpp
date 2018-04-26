#include "IsingMeantimeQuantities.h"

namespace PhaseTransition
{
	IsingMeantimeQuantities::IsingMeantimeQuantities(double T, double H, double H2, double M, double M2)
		: T(T), H(H), H2(H2), M(M), M2(M2)
	{
	}

	IsingMeantimeQuantities::~IsingMeantimeQuantities()
	{
	}

	double PhaseTransition::IsingMeantimeQuantities::getT()
	{
		return this->T;
	}

	double IsingMeantimeQuantities::getH()
	{
		return this->H;
	}

	double IsingMeantimeQuantities::getH2()
	{
		return this->H2;
	}

	double IsingMeantimeQuantities::getM()
	{
		return this->M;
	}

	double IsingMeantimeQuantities::getM2()
	{
		return this->M2;
	}
}