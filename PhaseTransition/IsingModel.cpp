#include <iostream>
#include "IsingModel.h"
#include "Randomizer.h"

namespace PhaseTransition
{
	IsingModel::IsingModel(IIsingIO& isingIO)
		: isingIO(isingIO), currentStepQuantities(IsingMeantimeQuantities::zeroes())
	{
	}

	IsingModel::~IsingModel()
	{
		int size = this->simParams->latticeSize;
		for (int i = 0; i < size; i++)
		{
			delete[] this->spins[i];
		}
		delete[] this->spins;
	}

	IsingSimulationParameters& IsingModel::getSimParams() const
	{
		return *this->simParams;
	}

	int IsingModel::getSpin(int i, int j) const
	{
		return this->spins[i][j];
	}

	void IsingModel::initialize(IsingSimulationParameters& simParams)
	{
		this->simParams = &simParams;
		initializeSpinsConfiguration();
	}

	void IsingModel::initialize(IsingSimulationParameters& simParams, int** spins)
	{
		this->simParams = &simParams;
		this->spins = spins;
	}

	void IsingModel::initializeSpinsConfiguration()
	{
		int latticeSize = this->simParams->latticeSize;
		int** spins = new int*[latticeSize];
		for (int i = 0; i < latticeSize; i++)
		{
			spins[i] = new int[latticeSize];
		}

		for (int i = 0; i < latticeSize; i++)
		{
			for (int j = 0; j < latticeSize; j++)
			{
				int spin = rand() % 2;
				if (spin == 0)
				{
					spin = -1;
				}
				spins[i][j] = spin;
			}
		}

		this->spins = spins;
	}	

	int IsingModel::neighboursSpinsSum(int i, int j) const
	{
		int up = i - 1;
		int down = i + 1;
		int left = j - 1;
		int right = j + 1;

		IsingSimulationParameters& simParams = *this->simParams;
		//Apply periodic boundary conditions
		if (up < 0) up = simParams.latticeSizeLessOne;
		if (down >= simParams.latticeSize) down = 0;
		if (left < 0) left = simParams.latticeSizeLessOne;
		if (right >= simParams.latticeSize) right = 0;

		int** spins = this->spins;
		int neighboursSpinsSum = spins[i][left] + spins[up][j] + spins[i][right] + spins[down][j];
		return neighboursSpinsSum;
	}

	double IsingModel::spinEnergy(int i, int j, int ijSpin) const
	{
		IsingSimulationParameters& simParams = *this->simParams;
		int ijNeighboursSpinsSum = neighboursSpinsSum(i, j);
		double energy = -ijSpin * ((simParams.J) * ijNeighboursSpinsSum + simParams.h);
		return energy;
	}

	double IsingModel::spinEnergyChange(int i, int j, int ijSpin) const
	{
		return -2 * spinEnergy(i, j, ijSpin);
	}

	double IsingModel::energy() const
	{
		double H = 0;
		int ijSpin;
		double ijAtomEnergy;
		int latticeSize = this->simParams->latticeSize;
		for (int i = 0; i < latticeSize; i++)
		{
			for (int j = 0; j < latticeSize; j++)
			{
				ijSpin = spins[i][j];
				ijAtomEnergy = spinEnergy(i, j, ijSpin);
				H += ijAtomEnergy;
			}
		}
		return 0.5 * H; // The factor 0.5 is needed, because in the loop each pair was calculated twice. TODO: Maybe this can be optimized?
	}

	int IsingModel::totalMagnetization() const
	{
		int totalM = 0;
		int** spins = this->spins;
		int latticeSize = this->simParams->latticeSize;
		for (int i = 0; i < latticeSize; i++)
		{
			for (int j = 0; j < latticeSize; j++)
			{
				totalM += spins[i][j];
			}
		}
		return totalM;
	}

	double IsingModel::magnetizationPerSite() const
	{
		int totalM = totalMagnetization();
		double MPerSite = totalM * this->simParams->latticeSizeFactor;
		return MPerSite;
	}

	IsingMeantimeQuantities& IsingModel::computeCurrentStepQuantities()
	{
		double E = energy();
		double M = magnetizationPerSite();
		this->currentStepQuantities = IsingMeantimeQuantities(E, M);
		return this->currentStepQuantities; // Return class member reference, to have this object alive beyond the method
		// And to not create it every time this method is called.
	}

	void IsingModel::simulationStep()
	{
		IsingSimulationParameters& simParams = *this->simParams;
		int** spins = this->spins;
		bool applySpinChange = true;
		double beta = simParams.beta;
		// Choose random atom
		int randomSpinNr = Randomizer::getInstance().randomNr(simParams.latticeSitesAmount);
		int i = randomSpinNr % simParams.latticeSize;
		int j = randomSpinNr / simParams.latticeSize;
		int ijSpin = spins[i][j];
		// Calculate energy change due to random spin flipping
		double deltaE = spinEnergyChange(i, j, ijSpin);
		// Apply spin change, when deltaE < 0 <=> E2 < E1 or with probability exp(-deltaE/T), when deltaE > 0 <=> E2 > E1
		if (deltaE > 0)
		{
			double boltzmanFactor = exp(-beta * deltaE);
			double random = Randomizer::getInstance().randomNrBetween0And1();
			if (random > boltzmanFactor)
				applySpinChange = false;
		}
		if (applySpinChange)
		{
			spins[i][j] = -ijSpin;
		}
	}

	void IsingModel::fullSimulationAfterInitialization()
	{
		IIsingIO& isingIO = this->isingIO;
		IsingSimulationParameters& simParams = *this->simParams;
		int mcsAmount = simParams.mcsAmount;
		int latticeSitesAmount = simParams.latticeSitesAmount;
		if (!simParams.saveMeantimeQuantities && !simParams.saveSpins)
		{
			for (int i = 1; i <= mcsAmount; i++)
			{
				for (int j = 1; j <= latticeSitesAmount; j++)
				{
					simulationStep();
				}
			}
		}
		else if (simParams.saveMeantimeQuantities && simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int i = 1; i <= latticeSitesAmount; i++)
				{
					simulationStep();
				}
				if (mcs % simParams.SAVING_MEANTIME_QUANTITIES_MCS_INTERVAL == 0)
				{
					IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
					isingIO.saveMeantimeQuantities(currentStepQuantieties, simParams, mcs);
					isingIO.saveSpins(*this, mcs);
				}
			}
		}
		else if (!simParams.saveMeantimeQuantities && simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int j = 1; j <= latticeSitesAmount; j++)
				{
					simulationStep();
				}
				if (mcs % simParams.SAVING_MEANTIME_QUANTITIES_MCS_INTERVAL == 0)
				{
					isingIO.saveSpins(*this, mcs);
				}
			}
		}
		else if (simParams.saveMeantimeQuantities && !simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int j = 1; j <= latticeSitesAmount; j++)
				{
					simulationStep();
				}
				if (mcs % simParams.SAVING_MEANTIME_QUANTITIES_MCS_INTERVAL == 0)
				{
					IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
					isingIO.saveMeantimeQuantities(currentStepQuantieties, simParams, mcs);
				}
			}
		}
	}

	void IsingModel::fullSimulation(IsingSimulationParameters& simParams)
	{
		initialize(simParams);
		fullSimulationAfterInitialization();
	}

	void IsingModel::fullSimulation(IsingSimulationParameters& simParams, int** initialSpinsConfiguration)
	{
		initialize(simParams, initialSpinsConfiguration);
		fullSimulationAfterInitialization();
	}
}