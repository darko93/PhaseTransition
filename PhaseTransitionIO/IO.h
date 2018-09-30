#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

namespace PhaseTransitionIO
{
	class IO
	{
	private:
		template<typename T>
		void split(const std::string& s, char delimiter, T result) const;
	protected:
		IO();
		std::string readLine(std::ifstream& ifstream) const;
		std::string readStringValue(const std::string& dataLine) const;
		std::string readStringValue(std::ifstream& ifstream) const;
		double readDoubleValue(const std::string& data) const;
		double readDoubleValue(std::ifstream& ifstream) const;
		int readIntValue(const std::string& data) const;
		int readIntValue(std::ifstream& ifstream) const;
		bool readBoolValue(const std::string& data) const;
		bool readBoolValue(std::ifstream& ifstream) const;
		int toInt(const std::string& s) const;
		double toDouble(const std::string& s) const;
		bool toBool(const std::string& s) const;
		std::string toFixedString(double d, int precision) const;
		std::vector<std::string> split(const std::string& s, char delimiter) const;
		//static std::ifstream* openIfstream(std::string filePath);
		//static std::fstream* openFstream(std::string filePath);
	public:
		//static void createFile(std::string& filePath);
	};
}

