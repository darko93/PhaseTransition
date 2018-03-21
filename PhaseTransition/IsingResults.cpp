#include "IsingResults.h"


namespace PhaseTransition
{
	IsingResults::IsingResults(double T, double M, double U, double Cv, double X)
		: T(T), M(M), U(U), Cv(Cv), X(X)
	{
	}

	IsingResults::IsingResults(double T, double U, double Cv, double X)
		: T(T), U(U), Cv(Cv), X(X)
	{
	}

	IsingResults::~IsingResults()
	{
	}

	double IsingResults::getT()
	{
		return this->T;
	}

	double IsingResults::getM()
	{
		return this->M;
	}

	double IsingResults::getU()
	{
		return this->U;
	}

	double IsingResults::getCv()
	{
		return this->Cv;
	}

	double IsingResults::getX()
	{
		return this->X;
	}
}
