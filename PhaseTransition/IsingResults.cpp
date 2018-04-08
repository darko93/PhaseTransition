#include "IsingResults.h"


namespace PhaseTransition
{
	IsingResults::IsingResults(double T, double U, double Cv, double M, double X)
		: T(T), U(U), Cv(Cv), M(M), X(X)
	{
	}

	IsingResults::~IsingResults()
	{
	}

	double IsingResults::getT()
	{
		return this->T;
	}

	double IsingResults::getU()
	{
		return this->U;
	}

	double IsingResults::getCv()
	{
		return this->Cv;
	}

	double IsingResults::getM()
	{
		return this->M;
	}

	double IsingResults::getX()
	{
		return this->X;
	}
}
