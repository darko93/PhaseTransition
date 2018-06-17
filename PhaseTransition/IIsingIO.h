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
		virtual IIsingInputData* readIsingInputData() = 0;
		virtual void createResultsFile(IsingSimulationParameters* simParams) = 0;
		virtual void saveResults(IsingResults* isingResults) = 0;
		virtual void createSpinsFile(IsingSimulationParameters* simParams) = 0;
		virtual void saveSpins(pht::IsingModel& isingModel) = 0;
		virtual void createMeantimeQuantitiesFile(IsingSimulationParameters* simParams) = 0;
		virtual void saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int step) = 0;
	};
}