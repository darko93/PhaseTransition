#pragma once

#include "IsingSimulationParameters.h"
#include "IsingQuantities.h"
#include "IsingResults.h"

namespace PhaseTransition
{
	class IsingModel
	{
	private:
		int** spins;
		IsingSimulationParameters* simParams;
		IsingQuantities* quantities;
		void initializeSpinsConfiguration();
		int neighboursSpinsSum(int i, int j, int ijSpin);
		double spinEnergy(int i, int j, int ijSpin);
		double spinEnergyChange(int i, int j, int ijSpin);
		double hamiltonian();
		int magnetization();
	public:
		IsingModel();
		IsingModel(IsingSimulationParameters* simParams);
		~IsingModel();
		int getSpin(int i, int j);
		IsingSimulationParameters* getSimParams();
		void initialize(IsingSimulationParameters* simParams);
		void initialize();
		IsingQuantities* simulationStep();
		IsingResults* fullSimulation(IsingSimulationParameters* simParams);
		IsingResults* fullSimulation();
		IsingResults* computeResults();
	};
}
