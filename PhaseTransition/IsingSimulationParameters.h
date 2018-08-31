#pragma once

#include "IsingModelType.h"

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
		friend class IIsingInputData;
	private:
		double T;
		const double kB = 1; // Boltzman constant
		double J; // coupling strength, +1 - ferromagnetic, -1 - antiferromagnetic
		double h; // mu * H - external field strength
		double beta; // 1/T
		int latticeSize;
		int latticeSizeLessOne;
		int latticeSitesAmount; // = amount of loop single steps in one MCS
		int mcsAmount; // MCS-es amount
		bool saveSpins;
		bool saveMeantimeQuantities;
		int savingMeantimeQuantitiesMcsInterval = 1; // TODO: make it dependent on T and size (?)
		void setT(double T);
		void setJ(int J);
		void setLatticeSize(int latticeSize);
	public:
		IsingSimulationParameters(double T, int J, int latticeSize, double h = 0,
			bool saveSpins = false,	bool saveMeantimeQuantities = false);
		~IsingSimulationParameters();
		double getT();
		double getJ();
		double getkB();
		double geth();
		int getLatticeSize();
	};
}