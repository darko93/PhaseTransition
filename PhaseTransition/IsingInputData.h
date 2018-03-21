#pragma once

#include<iostream>

namespace PhaseTransitionIO
{
	class IsingInputData
	{
	private:
		double J;
		int latticeSize;
		double h;
		double minT;
		double maxT;
		double TStep;
		int TRepeats;
		std::string resultsFilePath;
		std::string spinsFilePath;
	public:
		IsingInputData(double J, int latticeSize, double h, double minT, double maxT, double ktStep,
			int TRepeat, std::string resultsFilePath, std::string spinsFilePath);
		~IsingInputData();
		double getJ();
		int getLatticeSize();
		double geth();
		double getMinT();
		double getMaxT();
		double getTStep();
		int getTRepeats();
		std::string getResultsFilePath();
		std::string getSpinsFilePath();
	};
}