#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

namespace PhaseTransitionIO
{
	class IO
	{
	protected:
		IO();
		std::string readStringValue(std::ifstream& ifstream);
		double readDoubleValue(std::ifstream& ifstream);
		int readIntValue(std::ifstream& ifstream);
		//static std::ifstream* openIfstream(std::string filePath);
		//static std::fstream* openFstream(std::string filePath);
	public:
		//static void createFile(std::string& filePath);
	};
}

