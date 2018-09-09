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

	std::cout << "J=" << isingSimParams->getJ() << std::endl << "kB=" << isingSimParams->getkB() << std::endl
		<< "h=" << isingSimParams->geth() << std::endl << "latticeSize=" << isingSimParams->getLatticeSize() << std::endl << std::endl;

	double minT = isingSimParams->getT();
	pht::IsingSimulationParameters* previousSimParams = nullptr;
	pht::IsingModel isingModel(isingIO);
	do
	{
		std::cout << "T=" << isingSimParams->getT() << std::endl;
		if (isingInputData->getSaveSpins())
		{
			isingIO.createSpinsFile(isingInputData->getSpinsFilePathPattern(), isingSimParams);
		}
		if (isingInputData->getSaveMeantimeQuanities())
		{
			isingIO.createMeantimeQuantitiesFile(isingInputData->getMeantimeQuantitiesFilePathPattern(), isingSimParams);
		}
		bool useLastSpinsConfiguration = isingInputData->getSaveSpins()
			&& isingInputData->getContinueWithLastSpinsConfiguration() && previousSimParams != nullptr;
		if (useLastSpinsConfiguration)
		{
			int** spins = isingIO.readLastSpinsConfiguration(isingInputData->getSpinsFilePathPattern(), previousSimParams);
			isingModel.fullSimulation(isingSimParams, spins);
		}
		else
		{
			isingModel.fullSimulation(isingSimParams);
		}
		delete previousSimParams;
		previousSimParams = new pht::IsingSimulationParameters(*isingSimParams);
	} while (isingInputData->toNextSimulationParameters(isingSimParams));

	//isingModel.fullSimulation(isingSimParams);

	//while (isingInputData->toNextSimulationParameters(isingSimParams))
	//{
	//	std::cout << "T=" << isingSimParams->getT() << std::endl;
	//	if (isingInputData->getSaveSpins())
	//	{
	//		isingIO.createSpinsFile(isingInputData->getSpinsFilePath(), isingSimParams);
	//	}
	//	isingIO.createMeantimeQuantitiesFile(isingInputData->getMeantimeQuantitiesFilePathPattern(), isingSimParams);
	//	isingModel.fullSimulation(isingSimParams);
	//}

	delete isingInputData;
	delete isingSimParams;

	//double J = isingInputData->getJ();
	//pht::IsingModelType modelType = (pht::IsingModelType)(int)J;
	//int latticeSize = isingInputData->getLatticeSize();
	//double h = isingInputData->geth();
	//double minT = isingInputData->getMinT();
	//double maxT = isingInputData->getMaxT();
	//double TStep = isingInputData->getTStep();
	//int TRepeats = isingInputData->getTRepeats();
	//std::string resultsFilePath = isingInputData->getResultsFilePath();
	//std::string spinsFilePath = isingInputData->getSpinsFilePath();
	//delete isingInputData;

	//pht::IsingSimulationParameters* isingSimParams = new pht::IsingSimulationParameters(minT, modelType, latticeSize, h);
	//isingIO.createResultsFile(resultsFilePath, isingSimParams);
	//isingIO.createSpinsFile(spinsFilePath, isingSimParams);
	//pht::IsingModel isingModel;
	//
	//std::cout << "J=" << isingSimParams->getJ() << std::endl << "kB=" << isingSimParams->getkB() << std::endl << "latticeSize=" 
	//	<< isingSimParams->getLatticeSize() << std::endl << "h=" << isingSimParams->geth() << std::endl << std::endl;

	//for (double T = minT; T <= maxT; T += TStep)
	//{
	//	std::cout << "T=" << T << std::endl;
	//	isingSimParams->setT(T);
	//	for (int i = 0; i < TRepeats; i++)
	//	{
	//		std::cout << "TRepeat=" << i + 1 << std::endl;
	//		pht::IsingResults* isingResults = isingModel.fullSimulation(isingSimParams);
	//		isingIO.saveResults(resultsFilePath, isingResults);
	//		isingIO.saveSpins(spinsFilePath, isingModel);
	//	}
	//}
	//delete isingSimParams;

	std::cout << "Finished!" << std::endl;
	std::cin.get();
	return 0;
}