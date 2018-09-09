#pragma once

#include<iostream>
#include<vector>

#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	class IIsingInputData
	{
	public:
		virtual ~IIsingInputData() {};
		virtual int getJ() = 0;
		virtual double geth() = 0;
		virtual int getLatticeSize() = 0;
		virtual int getMcsAmount() = 0;
		virtual double getMinT() = 0;
		virtual double getMaxT() = 0;
		virtual double getTStep() = 0;
		virtual int getRepeats() = 0; // Amount of simulations with the same parameters
		virtual bool getSaveSpins() = 0;
		virtual bool getSaveMeantimeQuanities() = 0;
		IsingSimulationParameters* toFirstSimulationParameters();
		bool toNextSimulationParameters(IsingSimulationParameters* simParams);
	};
}
