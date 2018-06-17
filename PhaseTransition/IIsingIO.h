#pragma once

#include<iostream>

#include "IIsingInputData.h"
#include "IsingResults.h"
#include "IsingSimulationParameters.h"
#include "IsingModel.h"
#include "IsingMeantimeQuantities.h"

namespace pht = PhaseTransition;

namespace PhaseTransition
{
	class IIsingIO
	{
	public:
		virtual ~IIsingIO() {};
		virtual IIsingInputData* readIsingInputData(std::ifstream& isingIfstream) = 0;
		virtual void createResultsFile(std::string filePath, IsingSimulationParameters* simParams) = 0;
		virtual void saveResults(std::string filePath, IsingResults* isingResults) = 0;
		virtual void createSpinsFile(std::string filePath, IsingSimulationParameters* simParams) = 0;
		virtual void saveSpins(std::string filePath, pht::IsingModel& isingModel) = 0;
		virtual void createMeantimeQuantitiesFile(std::string filePathPattern, IsingSimulationParameters* simParams) = 0;
		virtual void saveMeantimeQuantities(std::string filePathPattern, pht::IsingMeantimeQuantities& meantimeQuantities, int step) = 0;
	};
}