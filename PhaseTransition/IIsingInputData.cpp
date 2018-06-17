#include "IIsingInputData.h"

namespace PhaseTransition
{
	int IIsingInputData::getCorrelationTime(double T)
	{
		std::vector<CorrelationTime*> correlationTimes = this->getCorrelationTimes();
		size_t correlTimesAmount = correlationTimes.size();
		for (std::vector<CorrelationTime*>::size_type i = 0; i < correlTimesAmount; i++)
		{
			CorrelationTime* iCorrelTime = correlationTimes[i];
			if (iCorrelTime->contains(T))
			{
				return iCorrelTime->getCorrelationTime();
			}
		}
		throw std::invalid_argument("No correlation time found for given T.");
	}

	IsingSimulationParameters* IIsingInputData::toFirstSimulationParameters()
	{
		int correlTime = getCorrelationTime(getMinT());
		IsingSimulationParameters* simParams = new IsingSimulationParameters(getMinT(), (IsingModelType)getJ(), 
			getLatticeSize(), geth(), correlTime, getSaveFinalResults(), getSaveSpins(), getSaveMeantimeQuanities());
		return simParams;
	}

	bool IIsingInputData::toNextSimulationParameters(IsingSimulationParameters* simParams)
	{
		double nextT = simParams->getT() + getTStep();
		bool isInRange = nextT <= getMaxT();
		int correlationTime = getCorrelationTime(nextT);
		simParams->setT(nextT);
		simParams->correlationTime = correlationTime;
		return isInRange;
	}
}