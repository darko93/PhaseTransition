#include "IO.h"

namespace PhaseTransitionIO
{
	IO::IO()
	{
	}

	std::string IO::readStringValue(std::ifstream& ifstream)
	{
		std::string dataLine;
		getline(ifstream, dataLine);
		int lineLength = dataLine.length();
		int indexOfEquals = dataLine.find('=');
		std::string stringValue = dataLine.substr(indexOfEquals + 1, lineLength - 1);
		return stringValue;
	}

	double IO::readDoubleValue(std::ifstream& ifstream)
	{
		std::string stringValue = readStringValue(ifstream);
		double doubleValue = atof(stringValue.c_str());
		return doubleValue;
	}

	int IO::readIntValue(std::ifstream& ifstream)
	{
		std::string stringValue = readStringValue(ifstream);
		int intValue = atoi(stringValue.c_str());
		return intValue;
	}

	//std::ifstream* IO::openIfstream(std::string filePath)
	//{
	//	std::ifstream* ifstream = new std::ifstream;
	//	ifstream->open(filePath.c_str(), std::ios::out);
	//	return ifstream;
	//}

	//std::fstream* IO::openFstream(std::string filePath)
	//{
	//	std::fstream* fstream = new std::fstream;
	//	fstream->open(filePath.c_str(), std::ios::out);
	//	return fstream;
	//}

	//void IO::createFile(std::string& filePath)
	//{
	//	std::fstream fstream;
	//	fstream.open(filePath.c_str(), std::ios::out);
	//	fstream.close();
	//}
}