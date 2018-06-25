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

	pht::IIsingInputData* IsingIO::readIsingInputData(std::string inputDataFilePath)
	{
		std::ifstream isingIfstream(inputDataFilePath);
		int J = readIntValue(isingIfstream);
		int latticeSize = readIntValue(isingIfstream);
		double h = readDoubleValue(isingIfstream);
		double minT = readDoubleValue(isingIfstream);
		double maxT = readDoubleValue(isingIfstream);
		double TStep = readDoubleValue(isingIfstream);
		int TRepeats = readIntValue(isingIfstream);
		bool saveFinalResults = readBoolValue(isingIfstream);
		std::string resultsFilePath = readStringValue(isingIfstream);
		bool saveSpins = readBoolValue(isingIfstream);
		std::string spinsFilePathPattern = readStringValue(isingIfstream);
		bool saveMeantimeQuantities = readBoolValue(isingIfstream);
		int savingMeantimeQuantitesInterval = readIntValue(isingIfstream);
		std::string meantimeQuantitiesFilePathPattern = readStringValue(isingIfstream);

		int correlationTimesAmount = readIntValue(isingIfstream);
		std::vector<pht::CorrelationTime*> correlationTimes;
		for (int i = 0; i < correlationTimesAmount; i++)
		{
			std::string correlationTimeLine = readLine(isingIfstream);
			std::vector<std::string> correlationTimeData = split(correlationTimeLine, ';');
			int correlTime = readIntValue(correlationTimeData[0]);
			double minT = readDoubleValue(correlationTimeData[1]);
			double maxT = readDoubleValue(correlationTimeData[2]);
			pht::CorrelationTime* correlationTime = new pht::CorrelationTime(correlTime, minT, maxT);
			correlationTimes.push_back(correlationTime);
		}

		IsingInputData* isingInputData = new IsingInputData();
		isingInputData->J = J;
		isingInputData->latticeSize = latticeSize;
		isingInputData->h = h;
		isingInputData->minT = minT;
		isingInputData->maxT = maxT;
		isingInputData->TStep = TStep;
		isingInputData->TRepeats = TRepeats;
		isingInputData->saveFinalResults = saveFinalResults;
		isingInputData->resultsFilePath = resultsFilePath;
		isingInputData->saveSpins = saveSpins;
		isingInputData->spinsFilePathPattern = spinsFilePathPattern;
		isingInputData->saveMeantimeQuantities = saveMeantimeQuantities;
		isingInputData->savingMeantimeQuantitiesInterval = savingMeantimeQuantitesInterval;
		isingInputData->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern;
		isingInputData->correlationTimes = correlationTimes;
		return isingInputData;
	}

	void IsingIO::createResultsFile(std::string resultsFilePath, pht::IsingSimulationParameters* simParams)
	{
		this->resultsFilePath = resultsFilePath;
		std::fstream fstream;
		fstream.open(resultsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize="
			<< simParams->getLatticeSize() << std::endl << "h=" << simParams->geth() << std::endl << std::endl;
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << "T" << std::setw(width) << "U" << std::setw(width)
			<< "Cv" << std::setw(width) << "M" << std::setw(width) << "X" << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveResults(pht::IsingResults* isingResults)
	{
		std::fstream fstream;
		fstream.open(this->resultsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << isingResults->getT() << std::setw(width) << isingResults->getU()
			<< std::setw(width) << isingResults->getCv() << std::setw(width) << isingResults->getM()
			<< std::setw(width) << isingResults->getX() << std::endl;
		fstream.close();
	}

	void IsingIO::createSpinsFile(std::string spinsFilePathPattern, pht::IsingSimulationParameters* simParams)
	{
		this->spinsFilePathPattern = spinsFilePathPattern;
		std::fstream fstream;
		std::string spinsFilePath = getFilePath(spinsFilePathPattern, simParams->getT());
		fstream.open(spinsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << "T=" << simParams->getT() << std::endl << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() 
			<< std::endl << "latticeSize=" << simParams->getLatticeSize() << std::endl << "h=" << simParams->geth() 
			<< std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveSpins(pht::IsingModel& isingModel)
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
		fstream << spinsString.str();
		fstream.close();
	}

	void IsingIO::createMeantimeQuantitiesFile(std::string meantimeQuantitiesFilePathPattern, 
		pht::IsingSimulationParameters* simParams)
	{
		this->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern;
		std::fstream fstream;
		std::string filePath = getFilePath(meantimeQuantitiesFilePathPattern, simParams->getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "T=" << simParams->getT() << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() 
			<< std::endl << "latticeSize=" << simParams->getLatticeSize() << std::endl << "h=" << simParams->geth() 
			<< std::endl << std::endl << std::endl << std::endl;
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << "step" << std::setw(width) << "H" << std::setw(width) << "H2" << std::setw(width)
			<< "M" << std::setw(width) << "M2" << std::endl;
		fstream.close();
	}

	void IsingIO::saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int step)
	{
		std::fstream fstream;
		std::string filePath = getFilePath(this->meantimeQuantitiesFilePathPattern, meantimeQuantities.getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << step << std::setw(width) << meantimeQuantities.getH() << std::setw(width) 
			<< meantimeQuantities.getH2() << std::setw(width) << meantimeQuantities.getM() << std::setw(width) 
			<< meantimeQuantities.getM2() << std::endl;
		fstream.close();
	}
}