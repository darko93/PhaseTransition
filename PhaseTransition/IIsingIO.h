#pragma once

#include<iostream>

#include "IIsingInputData.h"
#include "IsingQuantities.h"
#include "IsingResults.h"
#include "IsingSimulationParameters.h"

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
		//virtual void saveSpins(std::string filePath, pht::IsingModel& isingModel) = 0;
		virtual void createMeanTimeQuantities(std::string filePath, IsingSimulationParameters* simParams) = 0;
		virtual void saveMeanTimeQuantities(std::string filePath, IsingQuantities* quantities, int step) = 0;
	};
}