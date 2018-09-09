#include <sstream>
#include <fstream>

#include "IsingIO.h"
#include "IsingSimulationParameters.h"

namespace PhaseTransitionIO
{
	IsingIO::IsingIO()
	{
	}

	IsingIO::~IsingIO()
	{
	}

	std::string IsingIO::getFilePath(std::string filePathPattern, pht::IsingSimulationParameters* simParams)
	{
		std::string filePath;
		filePath = filePathPattern + "_LatticeSize=" + std::to_string(simParams->getLatticeSize()) 
			+ "_T=" + std::to_string(simParams->getT()) + "_h=" + std::to_string(simParams->geth());

		if (simParams->getRepeat() == 1)
		{
			filePath += ".txt";
		}
		else
		{
			filePath += "_Repeat=" + std::to_string(simParams->getRepeat()) + ".txt";
		}
		return filePath;
	}

	IsingInputData* IsingIO::readIsingInputData(std::string inputDataFilePath)
	{
		std::ifstream isingIfstream(inputDataFilePath);
		int J = readIntValue(isingIfstream);
		int minLatticeSize = readIntValue(isingIfstream);
		int maxLatticeSize = readIntValue(isingIfstream);
		int latticeSizeStep = readIntValue(isingIfstream);
		double minT = readDoubleValue(isingIfstream);
		double maxT = readDoubleValue(isingIfstream);
		double TStep = readDoubleValue(isingIfstream);
		double minh = readDoubleValue(isingIfstream);
		double maxh = readDoubleValue(isingIfstream);
		double hStep = readDoubleValue(isingIfstream);
		int mcsAmount = readIntValue(isingIfstream);
		int repeats = readIntValue(isingIfstream);
		bool saveSpins = readBoolValue(isingIfstream);
		std::string spinsFilePathPattern = readStringValue(isingIfstream);
		bool saveMeantimeQuantities = readBoolValue(isingIfstream);
		std::string meantimeQuantitiesFilePathPattern = readStringValue(isingIfstream);
		bool continueWithLastSpinsConfiguration = readBoolValue(isingIfstream);

		IsingInputData* isingInputData = new IsingInputData();
		isingInputData->J = J;
		isingInputData->minLatticeSize = minLatticeSize;
		isingInputData->maxLatticeSize = maxLatticeSize;
		isingInputData->latticeSizeStep = latticeSizeStep;
		isingInputData->minT = minT;
		isingInputData->maxT = maxT;
		isingInputData->TStep = TStep;
		isingInputData->minh = minh;
		isingInputData->maxh = maxh;
		isingInputData->hStep = hStep;
		isingInputData->mcsAmount = mcsAmount;
		isingInputData->repeats = repeats;
		isingInputData->saveSpins = saveSpins;
		isingInputData->spinsFilePathPattern = spinsFilePathPattern;
		isingInputData->saveMeantimeQuantities = saveMeantimeQuantities;
		isingInputData->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern;
		isingInputData->continueWithLastSpinsConfiguration = continueWithLastSpinsConfiguration;
		return isingInputData;
	}

	void IsingIO::createSpinsFile(std::string spinsFilePathPattern, pht::IsingSimulationParameters* simParams)
	{
		this->spinsFilePathPattern = spinsFilePathPattern; // Setting it here and using in save method
		std::fstream fstream;
		std::string spinsFilePath = getFilePath(spinsFilePathPattern, simParams);
		fstream.open(spinsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << "T=" << simParams->getT() << std::endl << "kB=" << simParams->getkB() << std::endl 
			<< "J=" << simParams->getJ() << std::endl << "h=" << simParams->geth() << std::endl 
			<< "latticeSize=" << simParams->getLatticeSize() << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveSpins(pht::IsingModel& isingModel, int mcs)
	{
		pht::IsingSimulationParameters* simParams = isingModel.getSimParams();
		std::stringstream spinsString;
		int latticeSize = simParams->getLatticeSize();
		for (int i = 0; i < latticeSize; i++)
		{
			for (int j = 0; j < latticeSize; j++)
			{
				int ijSpin = isingModel.getSpin(i, j);
				if (ijSpin == -1)
				{
					ijSpin = 0;
				}
				spinsString << ijSpin;
			}
			spinsString << std::endl;
		}
		spinsString << std::endl;
		std::string spinsFilePath = getFilePath(this->spinsFilePathPattern, simParams);
		std::fstream fstream;
		fstream.open(spinsFilePath, std::ios::out | std::ios::app);
		fstream << "MCS=" << mcs << std::endl;
		fstream << spinsString.str();
		fstream.close();
	}

	void IsingIO::createMeantimeQuantitiesFile(std::string meantimeQuantitiesFilePathPattern,
		pht::IsingSimulationParameters* simParams)
	{
		this->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern; // Setting it here and using in save method
		std::fstream fstream;
		std::string filePath = getFilePath(meantimeQuantitiesFilePathPattern, simParams);
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "T=" << simParams->getT() << std::endl << "kB=" << simParams->getkB() << std::endl << "J="
			<< simParams->getJ() << std::endl << "h=" << simParams->geth() << std::endl << "latticeSize="
			<< simParams->getLatticeSize() << std::endl << std::endl << std::endl;
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(IsingIO::NARROW_COLUMN_WIDTH) << "MCS" << std::setw(width) << "H"
			<< std::setw(width) << "M" << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, pht::IsingSimulationParameters* simParams, int mcs)
	{
		std::fstream fstream;
		std::string filePath = getFilePath(this->meantimeQuantitiesFilePathPattern, simParams);
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(IsingIO::NARROW_COLUMN_WIDTH) << mcs << std::setw(width) << meantimeQuantities.getH()
			<< std::setw(width) << meantimeQuantities.getM() << std::endl;
		fstream.close();
	}

	int** IsingIO::readLastSpinsConfiguration(std::string spinsFilePathPattern, pht::IsingSimulationParameters* simParams)
	{
		std::string spinsFilePath = getFilePath(spinsFilePathPattern, simParams);
		std::ifstream spinsIfstream(spinsFilePath);
		int lastMcs = simParams->getLastSavedSpinsConfigurationMcs();
		std::string lastSpinsLine = "MCS=" + std::to_string(lastMcs);

		// Move to the last spins configuration
		std::string line;
		bool reachedLastSpins = false;
		while (!reachedLastSpins)
		{
			getline(spinsIfstream, line);
			reachedLastSpins = line == lastSpinsLine;
		}

		// Read last spins configuration
		int latticeSize = simParams->getLatticeSize();
		int** spins = new int*[latticeSize];
		for (int i = 0; i < latticeSize; i++)
		{
			spins[i] = new int[latticeSize];
			getline(spinsIfstream, line);
			for (int j = 0; j < latticeSize; j++)
			{
				int ijSpin = line.at(j) - '0'; // To properly convert ASCII spin to int.
				if (ijSpin == 0)
				{
					ijSpin = -1;
				}
				spins[i][j] = ijSpin;
			}
		}

		return spins;
	}
}