#include "SimulationsManager.h"
#include "INotifier.h"
#include "IsingModel.h"
#include "IsingIO.h"

namespace phtio = PhaseTransitionIO;

SimulationsManager::SimulationsManager(const INotifier& notifier)
	: notifier(&notifier)
{
}


SimulationsManager::~SimulationsManager()
{
}

void SimulationsManager::performAllSimulations() const
{
	const INotifier& notifier = *this->notifier;
	phtio::IsingIO isingIO;
	phtio::IsingInputData* inputData = isingIO.readIsingInputData("PhaseTransitionInput.txt");

	pht::IsingSimulationParameters* simParams = inputData->toFirstSimulationParameters();

	notifier.notifyConstSimParams(*simParams);

	double minT = simParams->getT();
	pht::IsingSimulationParameters* previousSimParams = nullptr;
	pht::IsingModel isingModel(isingIO);
	do
	{
		notifier.notifyMutableSimParams(*simParams);
		if (inputData->getSaveSpins())
		{
			isingIO.createSpinsFile(inputData->getSpinsFilePathPattern(), *simParams);
		}
		if (inputData->getSaveMeantimeQuanities())
		{
			isingIO.createMeantimeQuantitiesFile(inputData->getMeantimeQuantitiesFilePathPattern(), *simParams);
		}
		bool useLastSpinsConfiguration = inputData->getSaveSpins()
			&& inputData->getReuseSpins() && previousSimParams != nullptr
			&& previousSimParams->getLatticeSize() == simParams->getLatticeSize();
		if (useLastSpinsConfiguration)
		{
			int** spins = isingIO.readLastSpinsConfiguration(inputData->getSpinsFilePathPattern(), *previousSimParams);
			isingModel.fullSimulation(*simParams, spins);
		}
		else
		{
			isingModel.fullSimulation(*simParams);
		}

		isingIO.flushSpins(*simParams);
		isingIO.flushMeantimeQuantities(*simParams);
		delete previousSimParams;
		previousSimParams = new pht::IsingSimulationParameters(*simParams);
	} while (inputData->toNextSimulationParameters(*simParams));

	delete inputData;
	delete simParams;

	notifier.notifyFinishedSimulations();
}
