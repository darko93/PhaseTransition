#include <stdexcept>
#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	IsingSimulationParameters IsingSimulationParameters::getDefault()
	{
		return IsingSimulationParameters(1, 20, 2.269, 0.0, 300000);
	}

	IsingSimulationParameters::IsingSimulationParameters(int J, int L, double T, double h, int mcsAmount, int repeat, bool saveSpins, 
		int savingSpinsMcsInterval, bool saveMeantimeQuantities, bool reuseSpins)
		: h(h), mcsAmount(mcsAmount), repeat(repeat), saveSpins(saveSpins), savingSpinsMcsInterval(savingSpinsMcsInterval),
		  saveMeantimeQuantities(saveMeantimeQuantities), reuseSpins(reuseSpins)
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

	int IsingSimulationParameters::getMcsAmount() const
	{
		return this->mcsAmount;
	}

	int IsingSimulationParameters::getRepeat() const
	{
		return this->repeat;
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
		this->N = L * L;
		this->LFactor = 1.0 / this->N;
	}
}
