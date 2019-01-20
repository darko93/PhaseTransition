#include <fstream>

#include "IsingIO.h"
#include "IsingSimulationParameters.h"

namespace PhaseTransitionIO
{
	IsingIO::IsingIO()
		: spinsCount(0), meantimeQuantitiesCount(0)
	{
	}

	IsingIO::~IsingIO()
	{
	}

	std::string IsingIO::getFilePath(const std::string& filePathPattern, const pht::IsingSimulationParameters& simParams) const
	{
		int precision = IsingIO::PRECISION_IN_FILE_NAME;
		std::string T = toFixedString(simParams.getT(), precision);
		std::string h = toFixedString(simParams.geth(), precision);

		std::string filePath;
		filePath = filePathPattern + "_L=" + std::to_string(simParams.getL()) 
			+ "_T=" + T + "_h=" + h;

		std::string extension = ".dat";
		if (simParams.getRepeat() == 1)
		{
			filePath += extension;
		}
		else
		{
			filePath += "_Repeat=" + std::to_string(simParams.getRepeat()) + extension;
		}
		return filePath;
	}

	IsingInputData* IsingIO::readIsingInputData(const std::string& inputDataFilePath) const
	{
		std::ifstream isingIfstream(inputDataFilePath);
		int J = readIntValue(isingIfstream);
		int minL = readIntValue(isingIfstream);
		int maxL = readIntValue(isingIfstream);
		int LStep = readIntValue(isingIfstream);
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
		isingInputData->minL = minL;
		isingInputData->maxL = maxL;
		isingInputData->LStep = LStep;
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

	void IsingIO::createSpinsFile(const std::string& spinsFilePathPattern, const pht::IsingSimulationParameters& simParams)
	{
		this->spinsFilePathPattern = spinsFilePathPattern; // Setting it here and using in save method
		std::fstream fstream;
		std::string spinsFilePath = getFilePath(spinsFilePathPattern, simParams);
		fstream.open(spinsFilePath.c_str(), std::ios::out | std::ios::app);
		fstream << "#T=" << simParams.getT() << std::endl << "#kB=" << simParams.getkB() << std::endl
			<< "#J=" << simParams.getJ() << std::endl << "#L=" << simParams.getL() << std::endl
			<< "#h=" << simParams.geth() << std::endl << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveSpins(const pht::IsingModel& isingModel, int mcs)
	{
		pht::IsingSimulationParameters& simParams = isingModel.getSimParams();
		std::stringstream spinsStream;
		spinsStream << "MCS=" << mcs << std::endl;
		int L = simParams.getL();
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < L; j++)
			{
				int ijSpin = isingModel.getSpin(i, j);
				if (ijSpin == -1)
				{
					ijSpin = 0;
				}
				spinsStream << ijSpin;
			}
			spinsStream << std::endl;
		}
		spinsStream << std::endl;
		this->spinsStream << spinsStream.str();

		if (this->spinsCount < IsingIO::SPINS_BUFFER_SIZE)
		{
			this->spinsCount++;
		}
		else
		{
			flushSpinsWnenExist(simParams);
		}
	}

	void IsingIO::flushSpinsWnenExist(const pht::IsingSimulationParameters& simParams)
	{
		std::string spinsFilePath = getFilePath(this->spinsFilePathPattern, simParams);
		std::fstream fstream;
		fstream.open(spinsFilePath, std::ios::out | std::ios::app);
		fstream << this->spinsStream.str();
		fstream.close();
		this->spinsStream.str(std::string());
		this->spinsCount = 0;
	}

	void IsingIO::flushSpins(const pht::IsingSimulationParameters& simParams)
	{
		if (this->spinsCount > 0)
		{
			flushSpinsWnenExist(simParams);
		}
	}

	void IsingIO::createMeantimeQuantitiesFile(const std::string& meantimeQuantitiesFilePathPattern,
		const pht::IsingSimulationParameters& simParams)
	{
		this->meantimeQuantitiesFilePathPattern = meantimeQuantitiesFilePathPattern; // Setting it here and using in save method
		std::fstream fstream;
		std::string filePath = getFilePath(meantimeQuantitiesFilePathPattern, simParams);
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << "#T=" << simParams.getT() << std::endl << "#kB=" << simParams.getkB() << std::endl 
			<< "#J=" << simParams.getJ() << std::endl << "#L=" << simParams.getL() << std::endl 
			<< "#h=" << simParams.geth() << std::endl << std::endl << std::endl;
		int width = IsingIO::COLUMN_WIDTH;
		fstream << "#" << std::setw(IsingIO::NARROW_COLUMN_WIDTH - 1) << "MCS" << std::setw(width) << "E" // Reducing narrow column width because of a '#' char
			<< std::setw(width) << "M" << std::endl << std::endl;
		fstream.close();
	}

	void IsingIO::saveMeantimeQuantities(const pht::IsingMeantimeQuantities& meantimeQuantities, const pht::IsingSimulationParameters& simParams, int mcs)
	{
		int width = IsingIO::COLUMN_WIDTH;
		std::stringstream meantimeQuantitiesStream;
		meantimeQuantitiesStream << std::fixed << std::setw(IsingIO::NARROW_COLUMN_WIDTH) << mcs << std::setw(width)
			<< meantimeQuantities.getE() << std::setw(width) << meantimeQuantities.getM() << std::endl;
		this->meantimeQuantitiesStream << meantimeQuantitiesStream.str();

		if (this->meantimeQuantitiesCount < IsingIO::QUANTITIES_BUFFER_SIZE)
		{
			this->meantimeQuantitiesCount++;
		}
		else
		{
			flushMeantimeQuantitiesWhenExist(simParams);
		}
	}

	void IsingIO::flushMeantimeQuantitiesWhenExist(const pht::IsingSimulationParameters& simParams)
	{
		std::string filePath = getFilePath(this->meantimeQuantitiesFilePathPattern, simParams);
		std::fstream fstream;
		fstream.open(filePath.c_str(), std::ios::out | std::ios::app);
		fstream << this->meantimeQuantitiesStream.str();
		fstream.close();
		this->meantimeQuantitiesStream.str(std::string());
		this->meantimeQuantitiesCount = 0;
	}

	void IsingIO::flushMeantimeQuantities(const pht::IsingSimulationParameters& simParams)
	{
		if (this->meantimeQuantitiesCount > 0)
		{
			flushMeantimeQuantitiesWhenExist(simParams);
		}
	}

	int** IsingIO::readLastSpinsConfiguration(const std::string& spinsFilePathPattern, const pht::IsingSimulationParameters& simParams) const
	{
		std::string spinsFilePath = getFilePath(spinsFilePathPattern, simParams);
		std::ifstream spinsIfstream(spinsFilePath);
		int lastMcs = simParams.getLastSavedSpinsConfigurationMcs();
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
		int L = simParams.getL();
		int** spins = new int*[L];
		for (int i = 0; i < L; i++)
		{
			spins[i] = new int[L];
			getline(spinsIfstream, line);
			for (int j = 0; j < L; j++)
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