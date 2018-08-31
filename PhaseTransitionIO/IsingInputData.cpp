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

	int IsingInputData::getTRepeats()
	{
		return this->TRepeats;
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
}