#pragma once

#include "IsingModel.h"
#include "IsingResults.h"

#include "IO.h"
#include "IsingInputData.h"
#include "IsingSimulationParameters.h"

namespace pht = PhaseTransition;

namespace PhaseTransitionIO
{
	class IsingIO : public IO
	{
	private:
		static const int COLUMN_WIDTH = 22;
		static const int PRECISION = 4;
	public:
		static IsingInputData* readIsingInputData(std::ifstream& isingIfstream);
		static void createResultsFile(std::string filePath, pht::IsingSimulationParameters* simParams);
		static void saveResults(std::string filePath, pht::IsingResults* isingResults);
		static void createSpinsFile(std::string filePath, pht::IsingSimulationParameters* simParams);
		static void saveSpins(std::string filePath, pht::IsingModel& isingModel);
		static void createMeanTimeQuantities(std::string filePath, pht::IsingSimulationParameters* simParams);
		static void saveMeanTimeQuantities(std::string filePath, pht::IsingQuantities quantities, int step);
	};
}