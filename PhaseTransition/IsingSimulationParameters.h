#pragma once

#include "IsingModelType.h"

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
	private:
		static const int DEFAULT_CORRELATION_TIME = 1;
		double T;
		const double kB = 1; // Boltzman constant
		IsingModelType modelType;
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
		void setModelType(IsingModelType modelType);
		void setLatticeSize(int latticeSize);
	public:
		IsingSimulationParameters(double T, IsingModelType modelType, int latticeSize, double h = 0,
			int correlationTime = DEFAULT_CORRELATION_TIME, bool saveFinalResults = false, bool saveSpins = false,
			bool saveMeantimeQuantities = false);
		~IsingSimulationParameters();
		void setT(double T, int correlationTime = DEFAULT_CORRELATION_TIME);
		double getT();
		IsingModelType getModelType();
		int getJ();
		double getkB();
		double geth();
		int getLatticeSize();
	};
}