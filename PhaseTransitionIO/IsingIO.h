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
		std::string inputDataFilePath;
		std::string resultsFilePath;
		std::string spinsFilePath;
		std::string meantimeQuantitiesFilePathPattern;
		std::string getMeantimeQuantitesFilePath(double T);
	public:
		IsingIO(std::string inputDataFilePath, std::string resultsFilePath, std::string spinsFilePath, 
			std::string meantimeQuantitiesFilePathPattern);
		~IsingIO();

		pht::IIsingInputData* readIsingInputData() override;
		void createResultsFile(pht::IsingSimulationParameters* simParams) override;
		void saveResults(pht::IsingResults* isingResults) override;
		void createSpinsFile(pht::IsingSimulationParameters* simParams) override;
		void saveSpins(pht::IsingModel& isingModel) override;
		void createMeantimeQuantitiesFile(pht::IsingSimulationParameters* simParams) override;
		void saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int step) override;
	};
}