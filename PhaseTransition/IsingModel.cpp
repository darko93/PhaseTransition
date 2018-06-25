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

		delete this->quantities;
	}

	IsingSimulationParameters* IsingModel::getSimParams()
	{
		return this->simParams;
	}

	int IsingModel::getSpin(int i, int j)
	{
		return this->spins[i][j];
	}

	void IsingModel::initialize(IsingSimulationParameters* simParams)
	{
		this->simParams = simParams;
		IsingMeantimeQuantities zeroes = IsingMeantimeQuantities::zeroes();
		this->quantities = new IsingQuantities(simParams->latticeSitesAmount, simParams->stepsAmount, zeroes);
		initializeSpinsConfiguration();
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

	int IsingModel::neighboursSpinsSum(int i, int j, int ijSpin)
	{
		int up = i - 1;
		int down = i + 1;
		int left = j - 1;
		int right = j + 1;

		//Apply periodic boundary conditions
		IsingSimulationParameters* simParams = this->simParams;
		if (up < 0) up = simParams->latticeSizeLessOne;
		if (down >= simParams->latticeSize) down = 0;
		if (left < 0) left = simParams->latticeSizeLessOne;
		if (right >= simParams->latticeSize) right = 0;

		int** spins = this->spins;
		int neighboursSpinsSum = spins[i][left] + spins[up][j] + spins[i][right] + spins[down][j];
		return neighboursSpinsSum;
	}

	double IsingModel::spinEnergy(int i, int j, int ijSpin)
	{
		IsingSimulationParameters* simParams = this->simParams;
		int ijNeighboursSpinsSum = neighboursSpinsSum(i, j, ijSpin);
		double energy = -ijSpin * ((simParams->J) * ijNeighboursSpinsSum + simParams->h);
		return energy;
	}

	double IsingModel::spinEnergyChange(int i, int j, int ijSpin)
	{
		return -2 * spinEnergy(i, j, ijSpin);
	}

	double IsingModel::hamiltonian()
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
		return 0.5 * H; // The factor 0.5 is needed, because in the loop each pair was calculated twice.
	}

	int IsingModel::magnetization()
	{
		int M = 0;
		int** spins = this->spins;
		int latticeSize = this->simParams->latticeSize;
		for (int i = 0; i < latticeSize; i++)
		{
			for (int j = 0; j < latticeSize; j++)
			{
				M += spins[i][j];
			}
		}
		return M;
	}

	IsingMeantimeQuantities& IsingModel::computeCurrentStepQuantities()
	{
		double H = hamiltonian();
		double H2 = H * H;
		double M = magnetization();
		double M2 = M * M;
		this->currentStepQuantities = IsingMeantimeQuantities(this->simParams->T, H, H2, M, M2);
		return this->currentStepQuantities;
	}

	IsingQuantities* IsingModel::simulationStep(int step)
	{
		IsingSimulationParameters* simParams = this->simParams;
		int** spins = this->spins;
		bool applySpinChange = true;
		double beta = simParams->beta;
		// Choose random atom
		int randomSpinNr = Randomizer::getInstance().randomNr(simParams->latticeSitesAmount);
		int i = randomSpinNr % simParams->latticeSize;
		int j = randomSpinNr / simParams->latticeSize;
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

		IsingQuantities* quantities = this->quantities;
		if (step % simParams->correlationTime == 0)
		{
			IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
			quantities->addCurrentStepQuantities(currentStepQuantieties);
		}
		else
		{
			quantities->clearCurrentStepQuantities();
		}

		return quantities;
	}

	IsingResults* IsingModel::fullSimulation(IsingSimulationParameters* simParams)
	{
		initialize(simParams);
		int stepsAmount = simParams->stepsAmount;
		IIsingIO& isingIO = this->isingIO;
		if (!simParams->saveMeantimeQuantities && !simParams->saveSpins)
		{
			for (int i = 1; i <= stepsAmount; i++)
			{
				simulationStep(i);
			}
		}
		else if (simParams->saveMeantimeQuantities && simParams->saveSpins)
		{
			for (int i = 1; i <= stepsAmount; i++)
			{
				simulationStep(i);
				if (i % simParams->savingMeantimeQuantitiesInterval == 0 && simParams->meantimeQuantitiesAmount-- > 0)
				{
					IsingQuantities* quantities = this->quantities;
					if (quantities->wasQuantitiesCalculatedInCurrentStep())
					{
						IsingMeantimeQuantities currentStepQuantities = quantities->getCurrentStepQuantities();
						isingIO.saveMeantimeQuantities(currentStepQuantities, i);
					}
					else
					{
						IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
						isingIO.saveMeantimeQuantities(currentStepQuantieties, i);
					}
				}
				if (i % simParams->correlationTime == 0)
				{
					isingIO.saveSpins(*this);
				}
			}
		}
		else if (!simParams->saveMeantimeQuantities && simParams->saveSpins)
		{
			for (int i = 1; i <= stepsAmount; i++)
			{
				simulationStep(i);
				if (i % simParams->correlationTime == 0)
				{
					isingIO.saveSpins(*this);
				}
			}
		}
		else if (simParams->saveMeantimeQuantities && !simParams->saveSpins)
		{
			for (int i = 1; i <= stepsAmount; i++)
			{
				simulationStep(i);
				if (i % simParams->savingMeantimeQuantitiesInterval == 0 && simParams->meantimeQuantitiesAmount-- > 0)
				{
					IsingQuantities* quantities = this->quantities;
					if (quantities->wasQuantitiesCalculatedInCurrentStep())
					{
						IsingMeantimeQuantities& currentStepQuantities = quantities->getCurrentStepQuantities();
						isingIO.saveMeantimeQuantities(currentStepQuantities, i);
					}
					else
					{
						IsingMeantimeQuantities currentStepQuantieties = computeCurrentStepQuantities();
						isingIO.saveMeantimeQuantities(currentStepQuantieties, i);
					}
				}
			}
		}
		IsingResults* isingResults = computeResults();
		return isingResults;
	}

	IsingResults* IsingModel::computeResults()
	{
		IsingSimulationParameters* simParams = this->simParams;
		IsingResults* results = this->quantities->computeResults(simParams->T);
		return results;
	}
}