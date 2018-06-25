#pragma once

#include<iostream>

#include "IIsingInputData.h"
#include "IsingResults.h"
#include "IsingSimulationParameters.h"
#include "IsingMeantimeQuantities.h"

class IsingModel;

namespace pht = PhaseTransition;

namespace PhaseTransition
{
	class IIsingIO
	{
	public:
		virtual ~IIsingIO() {};
		virtual void saveResults(IsingResults* isingResults) = 0;
		virtual void saveSpins(pht::IsingModel& isingModel) = 0;
		virtual void saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int step) = 0;
	};
}