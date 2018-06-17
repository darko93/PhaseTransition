#include <stdexcept>
#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	IsingSimulationParameters::IsingSimulationParameters(double T, int J, int latticeSize, double h,
		int correlationTime, bool saveFinalResults, bool saveSpins, bool saveMeantimeQuantities, int savingMeantimeQuantitiesInterval)
		: h(h), correlationTime(correlationTime), saveFinalResults(saveFinalResults), saveSpins(saveSpins),
			saveMeantimeQuantities(saveMeantimeQuantities), savingMeantimeQuantitiesInterval(savingMeantimeQuantitiesInterval)
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
		int latticeSitesAmount = latticeSize * latticeSize;
		this->latticeSitesAmount = latticeSitesAmount;
		this->stepsAmount = latticeSitesAmount * latticeSitesAmount * latticeSitesAmount;
	}
}
