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
		int getJ() override;
		int getLatticeSize() override;
		double geth() override;
		double getMinT() override;
		double getMaxT() override;
		double getTStep() override;
		int getTRepeats() override;
		bool getSaveFinalResults() override;
		std::string getResultsFilePath() override;
		bool getSaveSpins() override;
		std::string getSpinsFilePath() override;
		bool getSaveMeantimeQuanities() override;
		int getSavingMeantimeQuantitiesInterval() override;
		std::string getMeantimeQuantitiesFilePathPattern() override;
		std::vector<pht::CorrelationTime*> getCorrelationTimes() override;
	public:
		//IsingInputData(int J, int latticeSize, double h, double minT, double maxT, double ktStep, int TRepeats, 
		//	bool saveFinalResults, std::string resultsFilePath, bool saveSpins, std::string spinsFilePath, 
		//	bool saveMeantimeQuantities, int savingMeantimeQuantitiesInterval, std::string meantimeQuantitiesFilePathPattern,
		//	std::vector<pht::CorrelationTime*> correlationTimes);
		IsingInputData();
		~IsingInputData();
	};
}