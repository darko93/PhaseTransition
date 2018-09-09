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

	int IsingInputData::getMinLatticeSize()
	{
		return this->minLatticeSize;
	}

	int IsingInputData::getMaxLatticeSize()
	{
		return this->maxLatticeSize;
	}

	int IsingInputData::getLatticeSizeStep()
	{
		return this->latticeSizeStep;
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

	double IsingInputData::getMinh()
	{
		return this->minh;
	}

	double IsingInputData::getMaxh()
	{
		return this->maxh;
	}

	double IsingInputData::gethStep()
	{
		return this->hStep;
	}

	int IsingInputData::getMcsAmount()
	{
		return this->mcsAmount;
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