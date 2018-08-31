#include "IIsingInputData.h"

namespace PhaseTransition
{
	IsingSimulationParameters* IIsingInputData::toFirstSimulationParameters()
	{
		IsingSimulationParameters* simParams = new IsingSimulationParameters(getMinT(), getJ(), getLatticeSize(), 
			geth(), getSaveSpins(), getSaveMeantimeQuanities());
		return simParams;
	}

	bool IIsingInputData::toNextSimulationParameters(IsingSimulationParameters* simParams)
	{
		double nextT = simParams->getT() + getTStep();
		bool isInRange = nextT <= getMaxT();
		simParams->setT(nextT);
		return isInRange;
	}
}