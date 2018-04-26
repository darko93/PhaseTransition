#include "IO.h"

namespace PhaseTransitionIO
{
	IO::IO()
	{
	}

	std::string IO::readLine(std::ifstream & ifstream)
	{
		std::string line;
		getline(ifstream, line);
		return line;
	}

	std::string IO::readStringValue(std::ifstream& ifstream)
	{
		std::string dataLine = readLine(ifstream);
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

	template<typename T>
	void IO::split(std::string s, char delimiter, T result)
	{
		std::stringstream sStream(s);
		std::string item;
		while (std::getline(sStream, item, delimiter))
		{
			*(result++) = item;
		}
	}

	std::vector<std::string> IO::split(std::string s, char delimiter)
	{
		std::vector<std::string> strings;
		split(s, delimiter, std::back_inserter(strings));
		return strings;
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