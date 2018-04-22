#pragma once

#include "IIsingIO.h"
#include "IIsingInputData.h"
#include "IsingModel.h"
#include "IsingResults.h"
#include "IsingSimulationParameters.h"

#include "IsingInputData.h"
#include "IO.h"

namespace pht = PhaseTransition;

namespace PhaseTransitionIO
{
	class IsingIO : public IO, pht::IIsingIO
	{
	private:
		static const int COLUMN_WIDTH = 22;
		static const int PRECISION = 4;
	public:
		pht::IIsingInputData* readIsingInputData(std::ifstream& isingIfstream);
		void createResultsFile(std::string filePath, pht::IsingSimulationParameters* simParams);
		void saveResults(std::string filePath, pht::IsingResults* isingResults);
		void createSpinsFile(std::string filePath, pht::IsingSimulationParameters* simParams);
		void saveSpins(std::string filePath, pht::IsingModel& isingModel);
		void createMeanTimeQuantities(std::string filePath, pht::IsingSimulationParameters* simParams);
		void saveMeanTimeQuantities(std::string filePath, pht::IsingQuantities* quantities, int step);
	};
}