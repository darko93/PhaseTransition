#include "IIsingInputData.h"

namespace PhaseTransition
{
	IsingSimulationParameters* IIsingInputData::toFirstSimulationParameters() const
	{
		int repeat = 1;
		IsingSimulationParameters* simParams = new IsingSimulationParameters(getJ(), getMinLatticeSize(), getMinT(), getMinh(),
			getMcsAmount(), repeat, getSaveSpins(), getSaveMeantimeQuanities(), getReuseSpins());
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

				int nextLatticeSize = simParams.latticeSize + getLatticeSizeStep();
				isInRange = nextLatticeSize <= getMaxLatticeSize();
				if (!isInRange || getMinLatticeSize() == getMaxLatticeSize())
				{
					return false;
				}
				simParams.setLatticeSize(nextLatticeSize);
				return true;
			}
			simParams.setT(nextT);
			return true;
		}
		simParams.h = nexth;
		return true;
	}
}