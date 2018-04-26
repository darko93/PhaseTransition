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
		//IIsingIO* isingIO;
		void initializeSpinsConfiguration();
		int neighboursSpinsSum(int i, int j, int ijSpin);
		double spinEnergy(int i, int j, int ijSpin);
		double spinEnergyChange(int i, int j, int ijSpin);
		double hamiltonian();
		int magnetization();
	public:
		IsingModel(/*IIsingIO* isingIO*/);
		IsingModel(/*IIsingIO* isingIO, */IsingSimulationParameters* simParams);
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
