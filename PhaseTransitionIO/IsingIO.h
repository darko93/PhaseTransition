#pragma once

#include "IIsingIO.h"
#include "IsingModel.h"
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
		std::string spinsFilePathPattern;
		std::string meantimeQuantitiesFilePathPattern;
		std::string getFilePath(std::string filePathPattern, double T);
	public:
		IsingIO();
		~IsingIO();
		IsingInputData* readIsingInputData(std::string inputDataFilePath);
		void createSpinsFile(std::string spinsFilePathPattern, pht::IsingSimulationParameters* simParams);
		void createMeantimeQuantitiesFile(std::string meantimeQuantitiesFilePathPattern, pht::IsingSimulationParameters* simParams);
		void saveSpins(pht::IsingModel& isingModel, int mcs) override;
		void saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int mcs) override;
	};
}