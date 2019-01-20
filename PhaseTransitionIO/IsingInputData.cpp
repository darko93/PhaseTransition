#include "IsingInputData.h"

namespace PhaseTransitionIO
{
	IsingInputData::IsingInputData()
	{
	}


	IsingInputData::~IsingInputData()
	{
	}

	int IsingInputData::getJ() const
	{
		return this->J;
	}

	int IsingInputData::getMinL() const
	{
		return this->minL;
	}

	int IsingInputData::getMaxL() const
	{
		return this->maxL;
	}

	int IsingInputData::getLStep() const
	{
		return this->LStep;
	}

	double IsingInputData::getMinT() const
	{
		return this->minT;
	}

	double IsingInputData::getMaxT() const
	{
		return this->maxT;
	}

	double IsingInputData::getTStep() const
	{
		return this->TStep;
	}

	double IsingInputData::getMinh() const
	{
		return this->minh;
	}

	double IsingInputData::getMaxh() const
	{
		return this->maxh;
	}

	double IsingInputData::gethStep() const
	{
		return this->hStep;
	}

	int IsingInputData::getMcsAmount() const
	{
		return this->mcsAmount;
	}

	int IsingInputData::getRepeats() const
	{
		return this->repeats;
	}

	bool IsingInputData::getSaveSpins() const
	{
		return this->saveSpins;
	}

	std::string IsingInputData::getSpinsFilePathPattern() const
	{
		return this->spinsFilePathPattern;
	}

	bool IsingInputData::getSaveMeantimeQuanities() const
	{
		return this->saveMeantimeQuantities;
	}

	std::string IsingInputData::getMeantimeQuantitiesFilePathPattern() const
	{
		return this->meantimeQuantitiesFilePathPattern;
	}

	bool IsingInputData::getContinueWithLastSpinsConfiguration() const
	{
		return this->continueWithLastSpinsConfiguration;
	}
}