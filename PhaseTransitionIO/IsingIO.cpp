#include <sstream>

#include "IsingIO.h"
#include "IsingSimulationParameters.h"

namespace PhaseTransitionIO
{
	IsingInputData* IsingIO::readIsingInputData(std::ifstream& isingIfstream)
	{
		double J = readDoubleValue(isingIfstream);
		int latticeSize = readIntValue(isingIfstream);
		double h = readDoubleValue(isingIfstream);
		double minT = readDoubleValue(isingIfstream);
		double maxT = readDoubleValue(isingIfstream);
		double TStep = readDoubleValue(isingIfstream);
		int TRepeats = readIntValue(isingIfstream);
		std::string resultsFilePath = readStringValue(isingIfstream);
		std::string spinsFilePath = readStringValue(isingIfstream);
		IsingInputData* isingInputData = new IsingInputData(J, latticeSize, h, minT, maxT, TStep, TRepeats, resultsFilePath, spinsFilePath);
		return isingInputData;
	}

	void IsingIO::createResultsFile(std::string filePath, pht::IsingSimulationParameters* simParams)
	{
		std::fstream fstream;
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "J=" << simParams->getJ() << std::endl << "kB=" << simParams->getkB() << std::endl << "latticeSize=" 
			<< simParams->getLatticeSize() << std::endl	<< "h=" << simParams->geth() << std::endl << std::endl;
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		fstream << std::setw(IsingIO::COLUMN_WIDTH) << "T" << std::setw(IsingIO::COLUMN_WIDTH) << "M" << std::setw(IsingIO::COLUMN_WIDTH)
			<< "U" << std::setw(IsingIO::COLUMN_WIDTH) << "Cv" << std::setw(IsingIO::COLUMN_WIDTH) << "X" << std::setw(IsingIO::COLUMN_WIDTH)
			<< "aveH" << std::setw(IsingIO::COLUMN_WIDTH) << "aveCv" << std::setw(IsingIO::COLUMN_WIDTH) << "aveM" 
			<< std::setw(IsingIO::COLUMN_WIDTH) << "aveX" << std::setw(IsingIO::COLUMN_WIDTH) << "aveMExp" << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveToFile(std::string filePath, pht::IsingResults* isingResults)
	{
		std::fstream fstream;
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << std::fixed << std::setprecision(IsingIO::PRECISION);
		fstream << std::setw(IsingIO::COLUMN_WIDTH) << isingResults->getT() << std::setw(IsingIO::COLUMN_WIDTH) << isingResults->getM()
			<< std::setw(IsingIO::COLUMN_WIDTH) << isingResults->getU() << std::setw(IsingIO::COLUMN_WIDTH) << isingResults->getCv()
			<< std::setw(IsingIO::COLUMN_WIDTH) << isingResults->getX()
			<< std::setw(IsingIO::COLUMN_WIDTH) << isingResults->aveH << std::setw(IsingIO::COLUMN_WIDTH) << isingResults->aveCv
			<< std::setw(IsingIO::COLUMN_WIDTH) << isingResults->aveM << std::setw(IsingIO::COLUMN_WIDTH) << isingResults->aveX
			<< std::setw(IsingIO::COLUMN_WIDTH) << isingResults->aveMExp << std::endl;
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

	void IsingIO::saveToFile(std::string filePath, pht::IsingModel& isingModel)
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

	
}