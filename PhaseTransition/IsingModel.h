#pragma once

#include "IsingSimulationParameters.h"
#include "IIsingIO.h"

namespace PhaseTransition
{
	class IsingModel
	{
	private:
		int** spins;
		IsingSimulationParameters* simParams;
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
		void simulationStep();
		void fullSimulation(IsingSimulationParameters* simParams);
	};
}
