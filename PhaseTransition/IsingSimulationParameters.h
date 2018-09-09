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
		double beta; // 1/T
		double J; // coupling strength, +1 - ferromagnetic, -1 - antiferromagnetic
		const double kB = 1; // Boltzman constant
		double h; // mu * H - external field strength
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
		IsingSimulationParameters(int J, double T, double h, int latticeSize, int mcsAmount,
			bool saveSpins,	bool saveMeantimeQuantities);
		~IsingSimulationParameters();
		double getT();
		double getJ();
		double getkB();
		double geth();
		int getLatticeSize();
		int getLastSavedSpinsConfigurationMcs();
	};
}