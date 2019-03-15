#pragma once

#include <sstream>
#include <string>
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
		static const int PRECISION_IN_FILE_NAME = 3;
		static const int SPINS_BUFFER_SIZE = 1000;
		static const int QUANTITIES_BUFFER_SIZE = 10000;
		std::string spinsFilePathPattern; // Will be set in create file method and used in save method.
		std::string meantimeQuantitiesFilePathPattern; // Will be set in create file method and used in save method.
		std::stringstream spinsStream;
		int spinsConfigsCount;
		std::stringstream meantimeQuantitiesStream;
		int meantimeQuantitiesCount;
		std::string getFilePath(const std::string& filePathPattern, const pht::IsingSimulationParameters& simParams) const;
		void flushSpinsWnenExist(const pht::IsingSimulationParameters& simParams);
		void flushMeantimeQuantitiesWhenExist(const pht::IsingSimulationParameters& simParams);
	public:
		IsingIO();
		~IsingIO();
		IsingInputData readIsingInputData(const std::string& inputDataFilePath) const;
		void createSpinsFile(const std::string& spinsFilePathPattern, const pht::IsingSimulationParameters& simParams);
		void saveSpins(const pht::IsingModel& isingModel) override;
		void flushSpins(const pht::IsingSimulationParameters& simParams);
		void createMeantimeQuantitiesFile(const std::string& meantimeQuantitiesFilePathPattern, const pht::IsingSimulationParameters& simParams);
		void saveMeantimeQuantities(const pht::IsingMeantimeQuantities& meantimeQuantities, const pht::IsingSimulationParameters& simParams, int mcs) override;
		void flushMeantimeQuantities(const pht::IsingSimulationParameters& simParams);
		int** readLastSpinsConfiguration(const std::string& spinsFilePathPattern, const pht::IsingSimulationParameters& simParams) const;
	};
}