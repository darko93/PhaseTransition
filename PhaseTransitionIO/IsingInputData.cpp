#include "IsingInputData.h"

namespace PhaseTransitionIO
{
	IsingInputData::IsingInputData(int J, int latticeSize, double h, double minT, double maxT, double ktStep, int TRepeats, 
		std::string resultsFilePath, std::string spinsFilePath, std::vector<pht::CorrelationTime*> correlationTimes)
		: J(J), latticeSize(latticeSize), h(h), minT(minT), maxT(maxT), TStep(ktStep),
		  TRepeats(TRepeats), resultsFilePath(resultsFilePath), spinsFilePath(spinsFilePath)
	{
	}

	IsingInputData::~IsingInputData()
	{
	}

	double IsingInputData::getJ()
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

	std::string IsingInputData::getResultsFilePath()
	{
		return this->resultsFilePath;
	}

	std::string IsingInputData::getSpinsFilePath()
	{
		return this->spinsFilePath;
	}

	bool IsingInputData::getSaveMeantimeQuanities()
	{
		return this->saveMeantimeQuantities;
	}

	int IsingInputData::getSavingMeantimeQuantitiesInterval()
	{
		return this->savingMeantimeQuantitiesInterval;
	}

	std::string IsingInputData::getMeantimeQuantitiesFilePathPattern()
	{
		return this->meantimeQuantitiesFilePathPattern;
	}

	std::vector<pht::CorrelationTime*> IsingInputData::getCorrelationTimes()
	{
		return this->correlationTimes;
	}

	int IsingInputData::getCorrelationTime(double T)
	{
		std::vector<pht::CorrelationTime*> correlationTimes = this->correlationTimes;
		size_t correlTimesAmount = correlationTimes.size();
		for (std::vector<pht::CorrelationTime*>::size_type i = 0; i < correlTimesAmount; i++)
		{
			pht::CorrelationTime* iCorrelTime = correlationTimes[i];
			if (iCorrelTime->contains(T))
			{
				return iCorrelTime->getCorrelationTime();
			}
		}
		throw std::invalid_argument("No correlation time found for given  T.");
	}
}