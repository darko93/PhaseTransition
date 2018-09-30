#include <string.h>
#include <sstream>
#include "IO.h"

namespace PhaseTransitionIO
{
	IO::IO()
	{
	}

	std::string IO::readLine(std::ifstream& ifstream) const
	{
		std::string line;
		getline(ifstream, line);
		return line;
	}

	// Reads value as string from the string like "variable=500", for which it returns "500"
	std::string IO::readStringValue(const std::string& data) const
	{
		int lineLength = (int)data.length();
		int indexOfEquals = data.find('=');
		std::string stringValue = data.substr(indexOfEquals + 1, lineLength - 1);
		return stringValue;
	}

	std::string IO::readStringValue(std::ifstream& ifstream) const
	{
		std::string dataLine = readLine(ifstream);
		return readStringValue(dataLine);
	}

	double IO::readDoubleValue(const std::string& data) const
	{
		std::string stringValue = readStringValue(data);
		return toDouble(stringValue);
	}

	double IO::readDoubleValue(std::ifstream& ifstream) const
	{
		std::string stringValue = readStringValue(ifstream);
		return toDouble(stringValue);
	}

	int IO::readIntValue(const std::string& data) const
	{
		std::string stringValue = readStringValue(data);
		return toInt(stringValue);
	}

	int IO::readIntValue(std::ifstream& ifstream) const
	{
		std::string stringValue = readStringValue(ifstream);
		return toInt(stringValue);
	}

	bool IO::readBoolValue(const std::string& data) const
	{
		std::string stringValue = readStringValue(data);
		return toBool(stringValue);
	}

	bool IO::readBoolValue(std::ifstream& ifstream) const
	{
		std::string stringValue = readStringValue(ifstream);
		return toBool(stringValue);
	}

	int IO::toInt(const std::string& s) const
	{
		return atoi(s.c_str());;
	}

	double IO::toDouble(const std::string& s) const
	{
		return atof(s.c_str());;
	}

	bool IO::toBool(const std::string& s) const
	{
		return s == "1" || 0 == strcmpi(s.c_str(), "true");
	}

	std::string IO::toFixedString(double d, int precision) const
	{
		std::stringstream sstream;
		sstream << std::fixed << std::setprecision(precision) << d;
		std::string result = sstream.str();
		return result;
	}

	template<typename T>
	void IO::split(const std::string& s, char delimiter, T result) const
	{
		std::stringstream sstream(s);
		std::string item;
		while (std::getline(sstream, item, delimiter))
		{
			*(result++) = item;
		}
	}

	std::vector<std::string> IO::split(const std::string& s, char delimiter) const
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