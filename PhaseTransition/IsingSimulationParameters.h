#pragma once

#include "IsingModelType.h"

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
		friend class IIsingInputData;
	private:
		static const int DEFAULT_CORRELATION_TIME = 1;
		double T;
		const double kB = 1; // Boltzman constant
		double J; // coupling strength, +1 - ferromagnetic, -1 - antiferromagnetic
		double h; // mu * H - external field strength
		double beta; // 1/T
		int latticeSize;
		int latticeSizeLessOne;
		int latticeSitesAmount;
		int stepsAmount;
		int correlationTime;
		bool saveFinalResults;
		bool saveSpins;
		bool saveMeantimeQuantities;
		int savingMeantimeQuantitiesInterval;
		void setT(double T);
		void setJ(int J);
		void setLatticeSize(int latticeSize);
	public:
		IsingSimulationParameters(double T, int J, int latticeSize, double h = 0,
			int correlationTime = DEFAULT_CORRELATION_TIME, bool saveFinalResults = false, bool saveSpins = false,
			bool saveMeantimeQuantities = false, int savingMeantimeQuantitiesInterval = 100);
		~IsingSimulationParameters();
		double getT();
		double getJ();
		double getkB();
		double geth();
		int getLatticeSize();
	};
}