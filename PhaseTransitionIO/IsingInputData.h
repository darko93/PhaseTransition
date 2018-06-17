#pragma once

#include <iostream>
#include <vector>

#include "IIsingInputData.h"
#include "IsingSimulationParameters.h"
#include "CorrelationTime.h"

namespace pht = PhaseTransition;

namespace PhaseTransitionIO
{
	class IsingInputData : public pht::IIsingInputData
	{
		friend class IsingIO;
	private:
		int J; // +1 for ferromagnetic, -1 for antiferromagnetic
		int latticeSize;
		double h;
		double minT;
		double maxT;
		double TStep;
		int TRepeats;
		std::string resultsFilePath;
		std::string spinsFilePath;
		bool saveFinalResults;
		bool saveSpins;
		bool saveMeantimeQuantities;
		int savingMeantimeQuantitiesInterval;
		std::string meantimeQuantitiesFilePathPattern;
		std::vector<pht::CorrelationTime*> correlationTimes;
	protected:
		int getJ();
		int getLatticeSize();
		double geth();
		double getMinT();
		double getMaxT();
		double getTStep();
		int getTRepeats();
		bool getSaveFinalResults();
		std::string getResultsFilePath();
		bool getSaveSpins();
		std::string getSpinsFilePath();
		bool getSaveMeantimeQuanities();
		int getSavingMeantimeQuantitiesInterval();
		std::string getMeantimeQuantitiesFilePathPattern();
		std::vector<pht::CorrelationTime*> getCorrelationTimes();
	public:
		//IsingInputData(int J, int latticeSize, double h, double minT, double maxT, double ktStep, int TRepeats, 
		//	bool saveFinalResults, std::string resultsFilePath, bool saveSpins, std::string spinsFilePath, 
		//	bool saveMeantimeQuantities, int savingMeantimeQuantitiesInterval, std::string meantimeQuantitiesFilePathPattern,
		//	std::vector<pht::CorrelationTime*> correlationTimes);
		IsingInputData();
		~IsingInputData();
	};
}