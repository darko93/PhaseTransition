#pragma once

#include<iostream>

namespace PhaseTransitionIO
{
	class IsingInputData
	{
	private:
		int J; // +1 for ferromagnetic model, -1 for antiferromagnetic model
		int latticeSize;
		double h;
		double minT;
		double maxT;
		double TStep;
		int TRepeats;
		std::string resultsFilePath;
		std::string spinsFilePath;
		bool saveMeantimeQuantities;
		int savingMeantimeQuantitiesInterval;
		std::string meantimeQuantitiesFilePathPattern;
	public:
		IsingInputData(int J, int latticeSize, double h, double minT, double maxT, double ktStep,
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
		bool getSaveMeantimeQuanities();
		int getSavingMeantimeQuantitiesInterval();
		std::string getMeantimeQuantitiesFilePathPattern();
	};
}