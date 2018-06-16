#pragma once

#include <iostream>
#include <vector>

#include "IIsingInputData.h"
#include "CorrelationTime.h"

namespace pht = PhaseTransition;

namespace PhaseTransitionIO
{
	class IsingInputData : public pht::IIsingInputData
	{
	private:
		int J; // +1 for ferromagnetic model, -1 for antiferromagnetic model
		int latticeSize;
		double h;
		double minT;
		double maxT;
		double TStep;
		int TRepeats;
		std::string resultsFilePath;
		std::string spinsFilePath;
		bool saveMeantimeQuantities;
		int savingMeantimeQuantitiesInterval;
		std::string meantimeQuantitiesFilePathPattern;
		std::vector<pht::CorrelationTime*> correlationTimes;
	public:
		IsingInputData(int J, int latticeSize, double h, double minT, double maxT, double ktStep, int TRepeat, 
			std::string resultsFilePath, std::string spinsFilePath, std::vector<pht::CorrelationTime*> correlationTimes);
		~IsingInputData();
		double getJ();
		int getLatticeSize();
		double geth();
		double getMinT();
		double getMaxT();
		double getTStep();
		int getTRepeats();
		std::string getResultsFilePath();
		std::string getSpinsFilePath();
		bool getSaveMeantimeQuanities();
		int getSavingMeantimeQuantitiesInterval();
		std::string getMeantimeQuantitiesFilePathPattern();
		std::vector<pht::CorrelationTime*> getCorrelationTimes();
		int getCorrelationTime(double T);
	};
}