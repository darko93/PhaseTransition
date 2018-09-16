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
		static const int NARROW_COLUMN_WIDTH = 10;
		static const int COLUMN_WIDTH = 25;
		static const int PRECISION = 4;
		std::string spinsFilePathPattern; // Will be set in create file method and used in save method.
		std::string meantimeQuantitiesFilePathPattern; // Will be set in create file method and used in save method.
		std::string getFilePath(const std::string& filePathPattern, const pht::IsingSimulationParameters& simParams) const;
	public:
		IsingIO();
		~IsingIO();
		IsingInputData* readIsingInputData(const std::string& inputDataFilePath) const;
		void createSpinsFile(const std::string& spinsFilePathPattern, const pht::IsingSimulationParameters& simParams);
		void createMeantimeQuantitiesFile(const std::string& meantimeQuantitiesFilePathPattern, const pht::IsingSimulationParameters& simParams);
		void saveSpins(const pht::IsingModel& isingModel, int mcs) const override;
		void saveMeantimeQuantities(const pht::IsingMeantimeQuantities& meantimeQuantities, const pht::IsingSimulationParameters& simParams, int mcs) const override;
		int** readLastSpinsConfiguration(const std::string& spinsFilePathPattern, const pht::IsingSimulationParameters& simParams) const;
	};
}