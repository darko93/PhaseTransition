#include <stdexcept>
#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	IsingSimulationParameters::IsingSimulationParameters(int J, int L, double T, double h, int mcsAmount,
		int repeat, bool saveSpins, bool saveMeantimeQuantities)
		: h(h), mcsAmount(mcsAmount), repeat(repeat), saveSpins(saveSpins), saveMeantimeQuantities(saveMeantimeQuantities)
	{
		setT(T);
		setJ(J);
		setL(L);
	}

	IsingSimulationParameters::~IsingSimulationParameters()
	{
	}

	double IsingSimulationParameters::getT() const
	{
		return this->T;
	}

	int IsingSimulationParameters::getJ() const
	{
		return this->J;
	}

	double IsingSimulationParameters::getkB() const
	{
		return this->kB;
	}

	double IsingSimulationParameters::geth() const
	{
		return this->h;
	}

	int IsingSimulationParameters::getL() const
	{
		return this->L;
	}

	int IsingSimulationParameters::getRepeat() const
	{
		return this->repeat;
	}

	int IsingSimulationParameters::getLastSavedSpinsConfigurationMcs() const
	{
		int lastMcs = (this->mcsAmount / this->SAVING_MEANTIME_QUANTITIES_MCS_INTERVAL) * this->SAVING_MEANTIME_QUANTITIES_MCS_INTERVAL;
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

	void IsingSimulationParameters::setL(int L)
	{
		this->L = L;
		this->LLessOne = L - 1;
		this->latticeSitesAmount = L * L;
		this->LFactor = 1.0 / this->latticeSitesAmount;
	}
}
