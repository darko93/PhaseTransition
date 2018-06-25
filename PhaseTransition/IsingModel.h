#pragma once

#include "IsingSimulationParameters.h"
#include "IsingQuantities.h"
#include "IsingResults.h"
#include "IIsingIO.h"

namespace PhaseTransition
{
	class IsingModel
	{
	private:
		int** spins;
		IsingSimulationParameters* simParams;
		IsingQuantities* quantities;
		IIsingIO& isingIO;
		IsingMeantimeQuantities currentStepQuantities;
		void initializeSpinsConfiguration();
		int neighboursSpinsSum(int i, int j, int ijSpin);
		double spinEnergy(int i, int j, int ijSpin);
		double spinEnergyChange(int i, int j, int ijSpin);
		double hamiltonian();
		int magnetization();
		IsingMeantimeQuantities& computeCurrentStepQuantities();
	public:
		IsingModel(IIsingIO& isingIO);
		~IsingModel();
		IsingSimulationParameters* getSimParams();
		int getSpin(int i, int j);
		void initialize(IsingSimulationParameters* simParams);
		IsingQuantities* simulationStep(int step);
		IsingResults* fullSimulation(IsingSimulationParameters* simParams);
		IsingResults* computeResults();
	};
}
