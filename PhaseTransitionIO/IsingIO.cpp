#include <sstream>

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

	std::string IsingIO::getFilePath(std::string filePathPattern, double T)
	{
		return filePathPattern + "_T=" + std::to_string(T) + ".txt";
	}

	IsingInputData* IsingIO::readIsingInputData(std::string inputDataFilePath)
	{
		std::ifstream isingIfstream(inputDataFilePath);
		int J = readIntValue(isingIfstream);
		double h = readDoubleValue(isingIfstream);
		int latticeSize = readIntValue(isingIfstream);
		int mcsAmount = readIntValue(isingIfstream);
		double minT = readDoubleValue(isingIfstream);
		double maxT = readDoubleValue(isingIfstream);
		double TStep = readDoubleValue(isingIfstream);
		int TRepeats = readIntValue(isingIfstream);
		bool saveSpins = readBoolValue(isingIfstream);
		std::string spinsFilePathPattern = readStringValue(isingIfstream);
		bool saveMeantimeQuantities = readBoolValue(isingIfstream);
		std::string meantimeQuantitiesFilePathPattern = readStringValue(isingIfstream);

		IsingInputData* isingInputData = new IsingInputData();
		isingInputData->J = J;
		isingInputData->h = h;
		isingInputData->latticeSize = latticeSize;
		isingInputData->mcsAmount = mcsAmount;
		isingInputData->minT = minT;
		isingInputData->maxT = maxT;
		isingInputData->TStep = TStep;
		isingInputData->TRepeats = TRepeats;
		isingInputData->saveSpins = saveSpins;
		isingInputData->spinsFilePathPattern = spinsFilePathPattern;
		isingInputData->saveMeantimeQuantities = saveMeantimeQuantities;
		isingInputData->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern;
		return isingInputData;
	}

	void IsingIO::createSpinsFile(std::string spinsFilePathPattern, pht::IsingSimulationParameters* simParams)
	{
		this->spinsFilePathPattern = spinsFilePathPattern; // Setting it here and using in save method
		std::fstream fstream;
		std::string spinsFilePath = getFilePath(spinsFilePathPattern, simParams->getT());
		fstream.open(spinsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << "T=" << simParams->getT() << std::endl << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() 
			<< std::endl << "h=" << simParams->geth() << std::endl << "latticeSize=" << simParams->getLatticeSize()
			<< std::endl << std::endl;
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
		std::string spinsFilePath = getFilePath(this->spinsFilePathPattern, simParams->getT());
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
		std::string filePath = getFilePath(meantimeQuantitiesFilePathPattern, simParams->getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "T=" << simParams->getT() << std::endl << "J=" << simParams->getJ() << std::endl << "kB=" 
			<< simParams->getkB() << std::endl << "h=" << simParams->geth() << std::endl << "latticeSize=" 
			<< simParams->getLatticeSize() << std::endl << std::endl << std::endl;
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(IsingIO::NARROW_COLUMN_WIDTH) << "MCS" << std::setw(width) << "H" 
			<< std::setw(width) << "M" << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int mcs)
	{
		std::fstream fstream;
		std::string filePath = getFilePath(this->meantimeQuantitiesFilePathPattern, meantimeQuantities.getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(IsingIO::NARROW_COLUMN_WIDTH) << mcs << std::setw(width) << meantimeQuantities.getH()
			<< std::setw(width) << meantimeQuantities.getM() << std::endl;
		fstream.close();
	}
}