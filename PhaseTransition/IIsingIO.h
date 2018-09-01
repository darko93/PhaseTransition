#pragma once

#include<iostream>

#include "IIsingInputData.h"
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
		virtual void saveSpins(int** spins, IsingSimulationParameters* simParams, int mcs) = 0;
		virtual void saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int mcs) = 0;
	};
}