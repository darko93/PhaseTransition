#include <iostream>
#include "IsingModel.h"
#include "Randomizer.h"

namespace PhaseTransition
{
	IsingModel::IsingModel(IIsingIO& isingIO)
		: simParams(IsingSimulationParameters::getDefault()), isingIO(isingIO), currentStepQuantities(IsingMeantimeQuantities::zeroes())
	{
	}

	IsingModel::~IsingModel()
	{
		int size = this->simParams.L;
		for (int i = 0; i < size; i++)
		{
			delete[] this->spins[i];
		}
		delete[] this->spins;
	}

	void IsingModel::setSimParams(IsingSimulationParameters& simParams)
	{
		this->simParams = simParams;
		Randomizer::getInstance().setMaxRandomIntNr(simParams.N - 1);
	}

	void IsingModel::initializeSpinsConfiguration()
	{
		int L = this->simParams.L;
		int** spins = new int*[L];
		for (int i = 0; i < L; i++)
		{
			spins[i] = new int[L];
		}

		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
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

	IsingSimulationParameters IsingModel::getSimParams() const
	{
		return this->simParams;
	}

	int IsingModel::getSpin(int i, int j) const
	{
		return this->spins[i][j];
	}

	void IsingModel::initialize(IsingSimulationParameters& simParams)
	{
		bool reuseSpins = simParams.reuseSpins && this->simParams.L == simParams.L && this->spins != NULL;
		setSimParams(simParams);
		if (!reuseSpins)
		{
			initializeSpinsConfiguration();
		}
	}

	void IsingModel::initialize(IsingSimulationParameters& simParams, int** spins)
	{
		setSimParams(simParams);
		this->spins = spins;
	}

	int IsingModel::neighboursSpinsSum(int i, int j) const
	{
		int up = i - 1;
		int down = i + 1;
		int left = j - 1;
		int right = j + 1;

		const IsingSimulationParameters& simParams = this->simParams;
		//Apply periodic boundary conditions
		if (up < 0) up = simParams.LLessOne;
		if (down >= simParams.L) down = 0;
		if (left < 0) left = simParams.LLessOne;
		if (right >= simParams.L) right = 0;

		int** spins = this->spins;
		int neighboursSpinsSum = spins[i][left] + spins[up][j] + spins[i][right] + spins[down][j];
		return neighboursSpinsSum;
	}

	int IsingModel::spinEnergy(int i, int j, int ijSpin) const
	{
		const IsingSimulationParameters& simParams = this->simParams;
		int ijNeighboursSpinsSum = neighboursSpinsSum(i, j);
		int energy = -ijSpin * (simParams.J * ijNeighboursSpinsSum + simParams.h);
		return energy;
	}

	int IsingModel::spinEnergyChange(int i, int j, int ijSpin) const
	{
		return -2 * spinEnergy(i, j, ijSpin);
	}

	int IsingModel::energy() const
	{
		int E = 0;
		int ijSpin;
		int ijAtomEnergy;
		int L = this->simParams.L;
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
			{
				ijSpin = spins[i][j];
				ijAtomEnergy = spinEnergy(i, j, ijSpin);
				E += ijAtomEnergy;
			}
		}
		E = (int)std::round(0.5 * E); // The factor 0.5 is needed, because in the loop each pair was calculated twice. TODO: Maybe this can be optimized?
		return E;
	}

	int IsingModel::totalMagnetization() const
	{
		int totalM = 0;
		int** spins = this->spins;
		int L = this->simParams.L;
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
			{
				totalM += spins[i][j];
			}
		}
		return totalM;
	}

	double IsingModel::magnetizationPerSite() const
	{
		int totalM = totalMagnetization();
		double MPerSite = totalM * this->simParams.LFactor;
		return MPerSite;
	}

	IsingMeantimeQuantities& IsingModel::computeCurrentStepQuantities()
	{
		int E = energy();
		int M = totalMagnetization();
		this->currentStepQuantities = IsingMeantimeQuantities(E, M);
		return this->currentStepQuantities; // Return class member reference, to have this object alive beyond the method
		// And to not create it every time this method is called.
	}

	void IsingModel::metropolisStep()
	{
		IsingSimulationParameters& simParams = this->simParams;
		int** spins = this->spins;
		bool applySpinChange = true;
		double beta = simParams.beta;
		// Choose random atom
		int randomSpinNr = Randomizer::getInstance().randomIntNr();
		int i = randomSpinNr % simParams.L;
		int j = randomSpinNr / simParams.L;
		int ijSpin = spins[i][j];
		// Calculate energy change due to random spin flipping
		double deltaE = spinEnergyChange(i, j, ijSpin);
		// Apply spin change, when deltaE < 0 <=> E2 < E1 or with probability exp(-beta*deltaE), when deltaE > 0 <=> E2 > E1
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
		IsingSimulationParameters& simParams = this->simParams;
		int mcsAmount = simParams.mcsAmount;
		int N = simParams.N;
		if (!simParams.saveMeantimeQuantities && !simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int i = 1; i <= N; i++)
				{
					metropolisStep();
				}
			}
		}
		else if (simParams.saveMeantimeQuantities && simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int i = 1; i <= N; i++)
				{
					metropolisStep();
				}
				IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
				isingIO.saveMeantimeQuantities(currentStepQuantieties, simParams, mcs);
				if (mcs % simParams.savingSpinsMcsInterval == 0)
				{
					isingIO.saveSpins(*this);
				}
			}
		}
		else if (!simParams.saveMeantimeQuantities && simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int i = 1; i <= N; i++)
				{
					metropolisStep();
				}
				if (mcs % simParams.savingSpinsMcsInterval == 0)
				{
					isingIO.saveSpins(*this);
				}
			}
		}
		else if (simParams.saveMeantimeQuantities && !simParams.saveSpins)
		{
			for (int mcs = 1; mcs <= mcsAmount; mcs++)
			{
				for (int i = 1; i <= N; i++)
				{
					metropolisStep();
				}
				IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
				isingIO.saveMeantimeQuantities(currentStepQuantieties, simParams, mcs);
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