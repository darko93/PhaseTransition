#pragma once

#include<iostream>
#include<vector>

#include "CorrelationTime.h"
#include "IsingSimulationParameters.h"

namespace PhaseTransition
{
	class IIsingInputData
	{
	public:
		virtual ~IIsingInputData() {};
		virtual int getJ() = 0;
		virtual int getLatticeSize() = 0;
		virtual double geth() = 0;
		virtual double getMinT() = 0;
		virtual double getMaxT() = 0;
		virtual double getTStep() = 0;
		virtual int getTRepeats() = 0;
		virtual bool getSaveFinalResults() = 0;
		virtual std::string getResultsFilePath() = 0;
		virtual bool getSaveSpins() = 0;
		virtual std::string getSpinsFilePath() = 0;
		virtual bool getSaveMeantimeQuanities() = 0;
		virtual int getSavingMeantimeQuantitiesInterval() = 0;
		virtual std::string getMeantimeQuantitiesFilePathPattern() = 0;
		virtual std::vector<CorrelationTime*> getCorrelationTimes() = 0;
		int getCorrelationTime(double T);
		IsingSimulationParameters* toFirstSimulationParameters();
		bool toNextSimulationParameters(IsingSimulationParameters* simParams);
	};
}
