#include "IIsingInputData.h"

namespace PhaseTransition
{
	IsingSimulationParameters* IIsingInputData::toFirstSimulationParameters()
	{
		int repeat = 1;
		IsingSimulationParameters* simParams = new IsingSimulationParameters(getJ(), getMinT(), geth(), getLatticeSize(),
			getMcsAmount(), repeat, getSaveSpins(), getSaveMeantimeQuanities());
		return simParams;
	}

	bool IIsingInputData::toNextSimulationParameters(IsingSimulationParameters* simParams)
	{
		int nextRepeatNr = simParams->repeat + 1;
		if (nextRepeatNr <= getRepeats())
		{
			simParams->repeat++;
			return true;
		}
		else
		{
			double nextT = simParams->getT() + getTStep();
			bool isInRange = nextT <= getMaxT();
			simParams->setT(nextT);
			simParams->repeat = 1;
			return isInRange;
		}
	}
}