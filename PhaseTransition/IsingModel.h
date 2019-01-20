#pragma once

#include "IsingSimulationParameters.h"
#include "IIsingIO.h"

namespace PhaseTransition
{
	class IsingModel
	{
	private:
		int** spins;
		IsingSimulationParameters simParams;
		IIsingIO& isingIO;
		IsingMeantimeQuantities currentStepQuantities;
		void setSimParams(IsingSimulationParameters& simParams);
		void initializeSpinsConfiguration();
		int neighboursSpinsSum(int i, int j) const;
		int spinEnergy(int i, int j, int ijSpin) const;
		int spinEnergyChange(int i, int j, int ijSpin) const;
		int energy() const;
		int totalMagnetization() const;
		double magnetizationPerSite() const;
		IsingMeantimeQuantities& computeCurrentStepQuantities();
		void fullSimulationAfterInitialization();
	public:
		IsingModel(IIsingIO& isingIO);
		~IsingModel();
		IsingSimulationParameters getSimParams() const;
		int getSpin(int i, int j) const;
		void initialize(IsingSimulationParameters& simParams);
		void initialize(IsingSimulationParameters& simParams, int** spins);
		void simulationStep();
		void fullSimulation(IsingSimulationParameters& simParams);
		void fullSimulation(IsingSimulationParameters& simParams, int** initialSpinsConfiguration);
	};
}
