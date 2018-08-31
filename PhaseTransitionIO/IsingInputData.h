#pragma once

#include <iostream>
#include <vector>

#include "IIsingInputData.h"
#include "IsingSimulationParameters.h"

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
		bool saveSpins;
		bool saveMeantimeQuantities;
		std::string spinsFilePathPattern;
		std::string meantimeQuantitiesFilePathPattern;
	public:
		IsingInputData();
		~IsingInputData();
		int getJ() override;
		int getLatticeSize() override;
		double geth() override;
		double getMinT() override;
		double getMaxT() override;
		double getTStep() override;
		int getTRepeats() override;
		bool getSaveSpins() override;
		bool getSaveMeantimeQuanities() override;
		std::string getSpinsFilePathPattern();
		std::string getMeantimeQuantitiesFilePathPattern();
	};
}