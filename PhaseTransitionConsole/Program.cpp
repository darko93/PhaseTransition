#include <iostream>

#include "IsingModel.h"
#include "IsingModelType.h"
#include "IsingSimulationParameters.h"
#include "IsingIO.h"
#include "IsingInputData.h"

namespace pht = PhaseTransition;
namespace phtio = PhaseTransitionIO;

int main()
{	
	//std::cout << system("cd");
	phtio::IsingIO isingIO;
	phtio::IsingInputData* isingInputData = isingIO.readIsingInputData("PhaseTransitionInput.txt");
	
	pht::IsingSimulationParameters* isingSimParams = isingInputData->toFirstSimulationParameters();

	std::cout << "J=" << isingSimParams->getJ() << std::endl << "kB=" << isingSimParams->getkB() << std::endl << std::endl;

	double minT = isingSimParams->getT();
	pht::IsingSimulationParameters* previousSimParams = nullptr;
	pht::IsingModel isingModel(isingIO);
	do
	{
		std::cout << "latticeSize=" << isingSimParams->getLatticeSize() << "\t"	<< "T=" << isingSimParams->getT() 
			<< "\t" << "h=" << isingSimParams->geth() << "\t" << "repeat=" << isingSimParams->getRepeat() << std::endl;
		if (isingInputData->getSaveSpins())
		{
			isingIO.createSpinsFile(isingInputData->getSpinsFilePathPattern(), *isingSimParams);
		}
		if (isingInputData->getSaveMeantimeQuanities())
		{
			isingIO.createMeantimeQuantitiesFile(isingInputData->getMeantimeQuantitiesFilePathPattern(), *isingSimParams);
		}
		bool useLastSpinsConfiguration = isingInputData->getSaveSpins()
			&& isingInputData->getContinueWithLastSpinsConfiguration() && previousSimParams != nullptr
			&& previousSimParams->getLatticeSize() == isingSimParams->getLatticeSize();
		if (useLastSpinsConfiguration)
		{
			int** spins = isingIO.readLastSpinsConfiguration(isingInputData->getSpinsFilePathPattern(), *previousSimParams);
			isingModel.fullSimulation(*isingSimParams, spins);
		}
		else
		{
			isingModel.fullSimulation(*isingSimParams);
		}
		delete previousSimParams;
		previousSimParams = new pht::IsingSimulationParameters(*isingSimParams);
	} while (isingInputData->toNextSimulationParameters(*isingSimParams));

	delete isingInputData;
	delete isingSimParams;

	std::cout << "Finished!" << std::endl;
	std::cin.get();
	return 0;
}