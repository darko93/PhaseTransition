#pragma once

#include "ModelType.h"

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
	private:
		double T;
		const double kB = 1; // Boltzman constant
		ModelType modelType;
		double J; // coupling strength
		double h; // mu * H - external field strength
		double beta; // 1/T
		int latticeSize;
		int latticeSizeLessOne;
		int latticeSitesAmount;
		int stepsAmount;
		void setModelType(ModelType modelType);
		void setLatticeSize(int latticeSize);
	public:
		IsingSimulationParameters(double T, ModelType modelType, int latticeSize, double h = 0);
		~IsingSimulationParameters();
		void setT(double T);
		double getT();
		ModelType getModelType();
		double getJ();
		double getkB();
		double geth();
		int getLatticeSize();
	};
}