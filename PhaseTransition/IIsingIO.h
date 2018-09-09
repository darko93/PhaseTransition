#pragma once

#include<iostream>

#include "IIsingInputData.h"
#include "IsingMeantimeQuantities.h"

class IsingModel;

namespace PhaseTransition
{
	class IIsingIO
	{
	public:
		virtual ~IIsingIO() {};
		virtual void saveSpins(IsingModel& isingModel, int mcs) = 0;
		virtual void saveMeantimeQuantities(IsingMeantimeQuantities& meantimeQuantities, IsingSimulationParameters* simParams, int mcs) = 0;
	};
}