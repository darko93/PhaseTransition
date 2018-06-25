#include "IsingSimulationsManager.h"

namespace PhaseTransition
{
	IsingSimulationsManager::IsingSimulationsManager(IsingModel& isingModel)
		: isingModel(isingModel)
	{
	}


	IsingSimulationsManager::~IsingSimulationsManager()
	{
	}

	void IsingSimulationsManager::performAllSimulations(IIsingIO& isingIO)
	{
		//std::ifstream isingIfstream("PhaseTransitionInput.txt");
		pht::IIsingInputData* isingInputData = isingIO.readIsingInputData();
		//
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

		//std::cout << "Finished!" << std::endl;
	}
}