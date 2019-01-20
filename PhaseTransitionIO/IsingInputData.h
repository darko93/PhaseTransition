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
		int minL;
		int maxL;
		int LStep;
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
		bool reuseSpins;
	public:
		IsingInputData();
		~IsingInputData();
		int getJ() const override;
		int getMinL() const override;
		int getMaxL() const override;
		int getLStep() const override;
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
		bool getReuseSpins() const override;
		std::string getSpinsFilePathPattern() const;
		std::string getMeantimeQuantitiesFilePathPattern() const;
	};
}