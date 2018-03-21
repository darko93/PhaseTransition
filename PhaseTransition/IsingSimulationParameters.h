#pragma once

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
	private:
		double T;
		double J; // coupling strength
		double h; // mu * H - external field strength
		double beta; // 1/T
		int latticeSize;
		int latticeSizeLessOne;
		int latticeSitesAmount;
		int stepsAmount;
		void setLatticeSize(int latticeSize);
	public:
		IsingSimulationParameters(double T, double J, int latticeSize, double h = 0);
		~IsingSimulationParameters();
		void setT(double T);
		double getT();
		double getJ();
		double geth();
		int getLatticeSize();
	};
}