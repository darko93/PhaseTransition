#include "IIsingInputData.h"

namespace PhaseTransition
{
	IsingSimulationParameters IIsingInputData::toFirstSimulationParameters() const
	{
		int repeat = 1;
		IsingSimulationParameters simParams = IsingSimulationParameters(getJ(), getMinL(), getMinT(), getMinh(),
			getMcsAmount(), repeat, getSaveSpins(), getSavingSpinsMcsInterval(), getSaveMeantimeQuanities(), getReuseSpins());
		return simParams;
	}

	bool IIsingInputData::toNextSimulationParameters(IsingSimulationParameters& simParams) const
	{
		int nextRepeatNr = simParams.repeat + 1;
		if (nextRepeatNr <= getRepeats())
		{
			simParams.repeat++;
			return true;
		}
		simParams.repeat = 1;

		bool isInRange = false;
		double nexth = simParams.h + gethStep();
		isInRange = nexth <= getMaxh();
		if (!isInRange || getMinh() == getMaxh())
		{
			simParams.h = getMinh();

			double nextT = simParams.T + getTStep();
			isInRange = nextT <= getMaxT();
			if (!isInRange || getMinT() == getMaxT())
			{
				simParams.setT(getMinT());

				int nextL = simParams.L + getLStep();
				isInRange = nextL <= getMaxL();
				if (!isInRange || getMinL() == getMaxL())
				{
					return false;
				}
				simParams.setL(nextL);
				return true;
			}
			simParams.setT(nextT);
			return true;
		}
		simParams.h = nexth;
		return true;
	}
}