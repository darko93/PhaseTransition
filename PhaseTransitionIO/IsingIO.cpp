#include <sstream>

#include "IsingIO.h"
#include "IsingSimulationParameters.h"

namespace PhaseTransitionIO
{
	std::string IsingIO::getMeantimeQuantitesFilePath(std::string filePathPattern, double T)
	{
		return filePathPattern + "T" + std::to_string(T) + ".txt";
	}

	pht::IIsingInputData* IsingIO::readIsingInputData(std::ifstream& isingIfstream)
	{
		int J = readIntValue(isingIfstream);
		int latticeSize = readIntValue(isingIfstream);
		double h = readDoubleValue(isingIfstream);
		double minT = readDoubleValue(isingIfstream);
		double maxT = readDoubleValue(isingIfstream);
		double TStep = readDoubleValue(isingIfstream);
		int TRepeats = readIntValue(isingIfstream);
		std::string resultsFilePath = readStringValue(isingIfstream);
		std::string spinsFilePath = readStringValue(isingIfstream);

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

		pht::IIsingInputData* isingInputData = new IsingInputData(J, latticeSize, h, minT, maxT, TStep, 
			TRepeats, resultsFilePath, spinsFilePath, correlationTimes);
		return isingInputData;
	}

	void IsingIO::createResultsFile(std::string filePath, pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize=" 
			<< simParams->getLatticeSize() << std::endl	<< "h=" << simParams->geth() << std::endl << std::endl;
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << "T" << std::setw(width) << "U" << std::setw(width)
			<< "Cv" << std::setw(width) << "M" << std::setw(width) << "X" << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveResults(std::string filePath, pht::IsingResults* isingResults)
	{
		std::fstream fstream;
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << isingResults->getT() << std::setw(width) << isingResults->getU()
			<< std::setw(width) << isingResults->getCv() << std::setw(width) << isingResults->getM() 
			<< std::setw(width) << isingResults->getX() << std::endl;
		fstream.close();
	}

	void IsingIO::createSpinsFile(std::string filePath, pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize=" 
			<< simParams->getLatticeSize() << std::endl	<< "h=" << simParams->geth() << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveSpins(std::string filePath, pht::IsingModel& isingModel)
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
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << spinsString.str();
		fstream.close();
	}

	void IsingIO::createMeanTimeQuantitiesFile(std::string filePathPattern, pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		std::string filePath = getMeantimeQuantitesFilePath(filePathPattern, simParams->getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize="
			<< simParams->getLatticeSize() << std::endl << "h=" << simParams->geth() << std::endl << std::endl
			<< "T=" << simParams->getT() << std::endl << std::endl << std::endl;
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << "H" << std::setw(width) << "H2" << std::setw(width)
			<< "M" << std::setw(width) << "M2" << std::endl;
		fstream.close();
	}

	void IsingIO::saveMeanTimeQuantities(std::string filePathPattern, pht::IsingMeantimeQuantities& meantimeQuantities, int step)
	{
		std::fstream fstream;
		std::string filePath = getMeantimeQuantitesFilePath(filePathPattern, meantimeQuantities.getT());
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		int width = IsingIO::COLUMN_WIDTH;
		fstream << std::setw(width) << meantimeQuantities.getH() << std::setw(width) << meantimeQuantities.getH2()
			<< std::setw(width) << meantimeQuantities.getM() << std::setw(width) << meantimeQuantities.getM2() << std::endl;
		fstream.close();
	}
}