#include "IsingInputData.h"
#include "IsingModelType.h"

namespace PhaseTransitionIO
{
	IsingInputData::IsingInputData()
	{
	}


	IsingInputData::~IsingInputData()
	{
	}

	int IsingInputData::getJ()
	{
		return this->J;
	}

	double IsingInputData::geth()
	{
		return this->h;
	}

	int IsingInputData::getLatticeSize()
	{
		return this->latticeSize;
	}

	int IsingInputData::getMcsAmount()
	{
		return this->mcsAmount;
	}

	double IsingInputData::getMinT()
	{
		return this->minT;
	}

	double IsingInputData::getMaxT()
	{
		return this->maxT;
	}

	double IsingInputData::getTStep()
	{
		return this->TStep;
	}

	int IsingInputData::getRepeats()
	{
		return this->repeats;
	}

	bool IsingInputData::getSaveSpins()
	{
		return this->saveSpins;
	}

	std::string IsingInputData::getSpinsFilePathPattern()
	{
		return this->spinsFilePathPattern;
	}

	bool IsingInputData::getSaveMeantimeQuanities()
	{
		return this->saveMeantimeQuantities;
	}

	std::string IsingInputData::getMeantimeQuantitiesFilePathPattern()
	{
		return this->meantimeQuantitiesFilePathPattern;
	}

	bool IsingInputData::getContinueWithLastSpinsConfiguration()
	{
		return this->continueWithLastSpinsConfiguration;
	}
}