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
		int minLatticeSize;
		int maxLatticeSize;
		int latticeSizeStep;
		double minT;
		double maxT;
		double TStep;
		double minh;
		double maxh;
		double hStep;
		int mcsAmount;
		int repeats; // Amount of simulations with the same parameters
		bool saveSpins;
		bool saveMeantimeQuantities;
		std::string spinsFilePathPattern;
		std::string meantimeQuantitiesFilePathPattern;
		bool continueWithLastSpinsConfiguration;
	public:
		IsingInputData();
		~IsingInputData();
		int getJ() override;
		int getMinLatticeSize() override;
		int getMaxLatticeSize() override;
		int getLatticeSizeStep() override;
		double getMinT() override;
		double getMaxT() override;
		double getTStep() override; 
		double getMinh() override;
		double getMaxh() override;
		double gethStep() override;
		int getMcsAmount() override;
		int getRepeats() override;
		bool getSaveSpins() override;
		bool getSaveMeantimeQuanities() override;
		std::string getSpinsFilePathPattern();
		std::string getMeantimeQuantitiesFilePathPattern();
		bool getContinueWithLastSpinsConfiguration();
	};
}