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
	class IsingIO : public IO, public pht::IIsingIO
	{
	private:
		static const int COLUMN_WIDTH = 22;
		static const int PRECISION = 4;
		std::string getMeantimeQuantitesFilePath(std::string filePathPattern, double T);
	public:
		pht::IIsingInputData* readIsingInputData(std::ifstream& isingIfstream);
		void createResultsFile(std::string filePath, pht::IsingSimulationParameters* simParams);
		void saveResults(std::string filePath, pht::IsingResults* isingResults);
		void createSpinsFile(std::string filePath, pht::IsingSimulationParameters* simParams);
		void saveSpins(std::string filePath, pht::IsingModel& isingModel);
		void createMeanTimeQuantitiesFile(std::string filePathPattern, pht::IsingSimulationParameters* simParams);
		void saveMeanTimeQuantities(std::string filePathPattern, pht::IsingMeantimeQuantities& meantimeQuantities, int step);
	};
}