#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	IsingSimulationParameters::IsingSimulationParameters(double T, double J, int latticeSize, double h) :
		J(J), h(h)
	{
		setT(T);
		setLatticeSize(latticeSize);
	}

	IsingSimulationParameters::~IsingSimulationParameters()
	{
	}

	void IsingSimulationParameters::setT(double T)
	{
		this->T = T;
		this->beta = 1 / T;
	}

	double IsingSimulationParameters::getT()
	{
		return this->T;
	}

	double IsingSimulationParameters::getJ()
	{
		return this->J;
	}

	double IsingSimulationParameters::geth()
	{
		return this->h;
	}

	int IsingSimulationParameters::getLatticeSize()
	{
		return this->latticeSize;
	}

	void IsingSimulationParameters::setLatticeSize(int latticeSize)
	{
		this->latticeSize = latticeSize;
		this->latticeSizeLessOne = latticeSize - 1;
		int latticeSitesAmount = latticeSize * latticeSize;
		this->latticeSitesAmount = latticeSitesAmount;
		this->stepsAmount = latticeSitesAmount * latticeSitesAmount * latticeSitesAmount;
	}
}
