#include <sstream>

#include "IsingIO.h"
#include "IsingSimulationParameters.h"

namespace PhaseTransitionIO
{
	std::string IsingIO::getMeantimeQuantitesFilePath(double T)
	{
		return this->meantimeQuantitiesFilePathPattern + "T" + std::to_string(T) + ".txt";
	}

	IsingIO::IsingIO(std::string inputDataFilePath, std::string resultsFilePath, std::string spinsFilePath, std::string meantimeQuantitiesFilePathPattern)
		: inputDataFilePath(inputDataFilePath), resultsFilePath(resultsFilePath), spinsFilePath(spinsFilePath),
		  meantimeQuantitiesFilePathPattern(meantimeQuantitiesFilePathPattern)
	{
	}

	IsingIO::~IsingIO()
	{
	}

	pht::IIsingInputData* IsingIO::readIsingInputData()
	{
		std::ifstream isingIfstream(this->inputDataFilePath);
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
		std::string spinsFilePath = readStringValue(isingIfstream);
		bool saveMeantimeQuantities = readBoolValue(isingIfstream);
		int savingMeantimeQuantitesInterval = readIntValue(isingIfstream);
		std::string meantimeQuantitiesFilePathPattern = readStringValue(isingIfstream);

		int correlationTimesAmount = readIntValue(isingIfstream);
		std::vector<pht::CorrelationTime*> correlationTimes;
		for (int i = 0; i < correlationTimesAmount; i++)
		{
			std::string correlationTimeLine = readLine(isingIfstream);
			std::vector<std::string> correlationTimeData = split(correlationTimeLine, ';');
			int correlTime = atoi(correlationTimeData[0].c_str());
			double minT = atof(correlationTimeData[1].c_str());
			double maxT = atof(correlationTimeData[2].c_str());
			pht::CorrelationTime* correlationTime = new pht::CorrelationTime(correlTime, minT, maxT);
			correlationTimes[i] = correlationTime;
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
		isingInputData->spinsFilePath = spinsFilePath;
		isingInputData->saveMeantimeQuantities = saveMeantimeQuantities;
		isingInputData->savingMeantimeQuantitiesInterval = savingMeantimeQuantitesInterval;
		isingInputData->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern;
		isingInputData->correlationTimes = correlationTimes;
		return isingInputData;
	}

	void IsingIO::createResultsFile(pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		fstream.open(this->resultsFilePath.c_str(), std::ios::out | std::ios::app);
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

	void IsingIO::createSpinsFile(pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		fstream.open(this->spinsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize="
			<< simParams->getLatticeSize() << std::endl << "h=" << simParams->geth() << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveSpins(pht::IsingModel& isingModel)
	{
		pht::IsingSimulationParameters* simParams = isingModel.getSimParams();
		std::stringstream spinsString;
		spinsString << "T=" << simParams->getT() << std::endl;
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
		std::fstream fstream;
		fstream.open(this->spinsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << spinsString.str();
		fstream.close();
	}

	void IsingIO::createMeantimeQuantitiesFile(pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		std::string filePath = getMeantimeQuantitesFilePath(simParams->getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize="
			<< simParams->getLatticeSize() << std::endl << "h=" << simParams->geth() << std::endl << std::endl
			<< "T=" << simParams->getT() << std::endl << std::endl << std::endl;
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << "H" << std::setw(width) << "H2" << std::setw(width)
			<< "M" << std::setw(width) << "M2" << std::endl;
		fstream.close();
	}

	void IsingIO::saveMeantimeQuantities(pht::IsingMeantimeQuantities& meantimeQuantities, int step)
	{
		std::fstream fstream;
		std::string filePath = getMeantimeQuantitesFilePath(meantimeQuantities.getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << meantimeQuantities.getH() << std::setw(width) << meantimeQuantities.getH2()
			<< std::setw(width) << meantimeQuantities.getM() << std::setw(width) << meantimeQuantities.getM2() << std::endl;
		fstream.close();
	}
}