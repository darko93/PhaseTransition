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
		int getJ() const override;
		int getMinLatticeSize() const override;
		int getMaxLatticeSize() const override;
		int getLatticeSizeStep() const override;
		double getMinT() const override;
		double getMaxT() const override;
		double getTStep() const override;
		double getMinh() const override;
		double getMaxh() const override;
		double gethStep() const override;
		int getMcsAmount() const override;
		int getRepeats() const override;
		bool getSaveSpins() const override;
		bool getSaveMeantimeQuanities() const override;
		std::string getSpinsFilePathPattern() const;
		std::string getMeantimeQuantitiesFilePathPattern() const;
		bool getContinueWithLastSpinsConfiguration() const;
	};
}