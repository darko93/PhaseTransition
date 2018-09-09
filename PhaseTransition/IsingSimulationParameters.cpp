#include <stdexcept>
#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	IsingSimulationParameters::IsingSimulationParameters(int J, double T, double h, int latticeSize, int mcsAmount,
		int repeat, bool saveSpins, bool saveMeantimeQuantities)
		: h(h), mcsAmount(mcsAmount), repeat(repeat), saveSpins(saveSpins), saveMeantimeQuantities(saveMeantimeQuantities)
	{
		setT(T);
		setJ(J);
		setLatticeSize(latticeSize);
	}

	IsingSimulationParameters::~IsingSimulationParameters()
	{
	}

	double IsingSimulationParameters::getT()
	{
		return this->T;
	}

	double IsingSimulationParameters::getJ()
	{
		return this->J;
	}

	double IsingSimulationParameters::getkB()
	{
		return this->kB;
	}

	double IsingSimulationParameters::geth()
	{
		return this->h;
	}

	int IsingSimulationParameters::getLatticeSize()
	{
		return this->latticeSize;
	}

	int IsingSimulationParameters::getRepeat()
	{
		return this->repeat;
	}

	int IsingSimulationParameters::getLastSavedSpinsConfigurationMcs()
	{
		int lastMcs = (this->mcsAmount / this->savingMeantimeQuantitiesMcsInterval) * this->savingMeantimeQuantitiesMcsInterval;
		return lastMcs;
	}

	void IsingSimulationParameters::setT(double T)
	{
		this->T = T;
		this->beta = 1 / T;
	}

	void IsingSimulationParameters::setJ(int J)
	{
		if (J != 1 && J != -1)
		{
			throw std::invalid_argument("J must be equal +1 for ferromagnetic model or -1 for antiferromagnetic model.");
		}
		this->J = J;
	}

	void IsingSimulationParameters::setLatticeSize(int latticeSize)
	{
		this->latticeSize = latticeSize;
		this->latticeSizeLessOne = latticeSize - 1;
		this->latticeSitesAmount = latticeSize * latticeSize;
	}
}
