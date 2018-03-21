#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

namespace PhaseTransitionIO
{
	class IO
	{
	private:
		IO();
	protected:
		static std::string readStringValue(std::ifstream& ifstream);
		static double readDoubleValue(std::ifstream& ifstream);
		static int readIntValue(std::ifstream& ifstream);
		//static std::ifstream* openIfstream(std::string filePath);
		//static std::fstream* openFstream(std::string filePath);
	public:
		//static void createFile(std::string& filePath);
	};
}

