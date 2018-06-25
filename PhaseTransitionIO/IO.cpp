#include "IO.h"

namespace PhaseTransitionIO
{
	IO::IO()
	{
	}

	std::string IO::readLine(std::ifstream& ifstream)
	{
		std::string line;
		getline(ifstream, line);
		return line;
	}

	// Reads value as string from the string like "variable=500", for which it returns "500"
	std::string IO::readStringValue(std::string data)
	{
		int lineLength = (int)data.length();
		int indexOfEquals = data.find('=');
		std::string stringValue = data.substr(indexOfEquals + 1, lineLength - 1);
		return stringValue;
	}

	std::string IO::readStringValue(std::ifstream& ifstream)
	{
		std::string dataLine = readLine(ifstream);
		return readStringValue(dataLine);
	}

	double IO::readDoubleValue(std::string data)
	{
		std::string stringValue = readStringValue(data);
		return toDouble(stringValue);
	}

	double IO::readDoubleValue(std::ifstream& ifstream)
	{
		std::string stringValue = readStringValue(ifstream);
		return toDouble(stringValue);
	}

	int IO::readIntValue(std::string data)
	{
		std::string stringValue = readStringValue(data);
		return toInt(stringValue);
	}

	int IO::readIntValue(std::ifstream& ifstream)
	{
		std::string stringValue = readStringValue(ifstream);
		return toInt(stringValue);
	}

	bool IO::readBoolValue(std::string data)
	{
		std::string stringValue = readStringValue(data);
		return toBool(stringValue);
	}

	bool IO::readBoolValue(std::ifstream& ifstream)
	{
		std::string stringValue = readStringValue(ifstream);
		return toBool(stringValue);
	}

	int IO::toInt(std::string s)
	{
		return atoi(s.c_str());;
	}

	double IO::toDouble(std::string s)
	{
		return atof(s.c_str());;
	}

	bool IO::toBool(std::string s)
	{
		return s == "1";
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