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
		void split(std::string s, char delimiter, T result);
	protected:
		IO();
		std::string readLine(std::ifstream& ifstream);
		std::string readStringValue(std::ifstream& ifstream);
		double readDoubleValue(std::ifstream& ifstream);
		int readIntValue(std::ifstream& ifstream);
		bool readBoolValue(std::ifstream& ifstream);
		bool toBool(std::string s);
		std::vector<std::string> split(std::string s, char delimiter);
		//static std::ifstream* openIfstream(std::string filePath);
		//static std::fstream* openFstream(std::string filePath);
	public:
		//static void createFile(std::string& filePath);
	};
}

