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
		std::string resultsFilePath;
		std::string spinsFilePathPattern;
		std::string meantimeQuantitiesFilePathPattern;
		std::string getFilePath(std::string filePathPattern, double T);
	public:
		IsingIO();
		~IsingIO();
		pht::IIsingInputData* readIsingInputData(std::string inputDataFilePath);
		void createResultsFile(std::string resultsFilePath, pht::IsingSimulationParameters* simParams);
		void saveResults(pht::IsingResults* isingResults) override;
		void createSpinsFile(std::string spinsFilePathPattern, pht::IsingSimulationParameters* simParams);
		void saveSpins(pht::IsingModel& isingModel) override;
		void createMeantimeQuantitiesFile(std::string meantimeQuantitiesFilePathPattern, pht::IsingSimulationParameters* simParams);
		void saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int step) override;
	};
}