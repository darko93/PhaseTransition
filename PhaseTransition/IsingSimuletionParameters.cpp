#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	IsingSimulationParameters::IsingSimulationParameters(double T, IsingModelType modelType, int latticeSize, double h) :
		h(h)
	{
		setT(T);
		setModelType(modelType);
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

	IsingModelType IsingSimulationParameters::getModelType()
	{
		return this->modelType;
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

	void IsingSimulationParameters::setModelType(IsingModelType modelType)
	{
		this->modelType = modelType;
		this->J = (double)modelType;
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
