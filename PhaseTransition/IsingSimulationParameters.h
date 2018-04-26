#pragma once

#include "IsingModelType.h"

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
	private:
		double T;
		const double kB = 1; // Boltzman constant
		IsingModelType modelType;
		double J; // coupling strength
		double h; // mu * H - external field strength
		double beta; // 1/T
		int latticeSize;
		int latticeSizeLessOne;
		int latticeSitesAmount;
		int stepsAmount;
		bool saveMeantimeQuantities;
		int correlationTime;
		void setModelType(IsingModelType modelType);
		void setLatticeSize(int latticeSize);
	public:
		IsingSimulationParameters(double T, IsingModelType modelType, int latticeSize, double h = 0, 
			bool saveMeantimeQuantities = false, int correlationTime = 1);
		~IsingSimulationParameters();
		void setT(double T);
		double getT();
		IsingModelType getModelType();
		double getJ();
		double getkB();
		double geth();
		int getLatticeSize();
	};
}