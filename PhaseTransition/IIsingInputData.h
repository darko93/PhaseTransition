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
		virtual int getJ() const = 0;
		virtual int getMinL() const = 0;
		virtual int getMaxL() const = 0;
		virtual int getLStep() const = 0;
		virtual double getMinT() const = 0;
		virtual double getMaxT() const = 0;
		virtual double getTStep() const = 0;
		virtual double getMinh() const = 0;
		virtual double getMaxh() const = 0;
		virtual double gethStep() const = 0;
		virtual int getMcsAmount() const = 0;
		virtual int getRepeats() const = 0; // Amount of simulations with the same parameters
		virtual bool getSaveSpins() const = 0;
		virtual int getSavingSpinsMcsInterval() const = 0;
		virtual bool getSaveMeantimeQuanities() const = 0;
		virtual bool getReuseSpins() const = 0;
		IsingSimulationParameters toFirstSimulationParameters() const;
		bool toNextSimulationParameters(IsingSimulationParameters& simParams) const;
	};
}
