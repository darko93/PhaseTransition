#include <iostream>

#include "IsingModel.h"
#include "ModelType.h"
#include "IsingSimulationParameters.h"
#include "IsingIO.h"

namespace pht = PhaseTransition;
namespace phtio = PhaseTransitionIO;

int main()
{	
	std::ifstream isingIfstream("PhaseTransitionInput.txt");
	phtio::IsingInputData* isingInputData = phtio::IsingIO::readIsingInputData(isingIfstream);
	
	double J = isingInputData->getJ();
	ModelType modelType = (ModelType)(int)J;
	int latticeSize = isingInputData->getLatticeSize();
	double h = isingInputData->geth();
	double minT = isingInputData->getMinT();
	double maxT = isingInputData->getMaxT();
	double TStep = isingInputData->getTStep();
	int TRepeats = isingInputData->getTRepeats();
	std::string resultsFilePath = isingInputData->getResultsFilePath();
	std::string spinsFilePath = isingInputData->getSpinsFilePath();
	delete isingInputData;

	pht::IsingSimulationParameters* isingSimParams = new pht::IsingSimulationParameters(minT, modelType, latticeSize, h);
	phtio::IsingIO::createResultsFile(resultsFilePath, isingSimParams);
	phtio::IsingIO::createSpinsFile(spinsFilePath, isingSimParams);
	pht::IsingModel isingModel;
	
	std::cout << "J=" << isingSimParams->getJ() << std::endl << "kB=" << isingSimParams->getkB() << std::endl << "latticeSize=" 
		<< isingSimParams->getLatticeSize() << std::endl << "h=" << isingSimParams->geth() << std::endl << std::endl;

	for (double T = minT; T <= maxT; T += TStep)
	{
		std::cout << "T=" << T << std::endl;
		isingSimParams->setT(T);
		for (int i = 0; i < TRepeats; i++)
		{
			std::cout << "TRepeat=" << i + 1 << std::endl;
			pht::IsingResults* isingResults = isingModel.fullSimulation(isingSimParams);
			phtio::IsingIO::saveToFile(resultsFilePath, isingResults);
			phtio::IsingIO::saveToFile(spinsFilePath, isingModel);
		}
	}
	delete isingSimParams;

	std::cout << "Finished!" << std::endl;
	std::cin.get();
	return 0;
}