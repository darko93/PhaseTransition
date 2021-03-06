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
	phtio::IsingInputData inputData = isingIO.readIsingInputData("PhaseTransitionInput.txt");

	pht::IsingSimulationParameters simParams = inputData.toFirstSimulationParameters();

	notifier.notifyConstSimParams(simParams);

	pht::IsingModel isingModel(isingIO);
	do
	{
		notifier.notifyMutableSimParams(simParams);
		if (inputData.getSaveSpins())
		{
			isingIO.createSpinsFile(inputData.getSpinsFilePathPattern(), simParams);
		}
		if (inputData.getSaveMeantimeQuanities())
		{
			isingIO.createMeantimeQuantitiesFile(inputData.getMeantimeQuantitiesFilePathPattern(), simParams);
		}
		isingModel.fullSimulation(simParams);

		isingIO.flushSpins(simParams);
		isingIO.flushMeantimeQuantities(simParams);
	} while (inputData.toNextSimulationParameters(simParams));

	notifier.notifyFinishedSimulations();
}
