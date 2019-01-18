#pragma once

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
		friend class IIsingInputData;
	private:
		const int SAVING_MEANTIME_QUANTITIES_MCS_INTERVAL = 1; // TODO (?): make it dependent on T and size
		const double kB = 1; // Boltzman constant
		double J; // coupling strength, +1 - ferromagnetic, -1 - antiferromagnetic
		double T;
		double beta; // 1/T
		double h; // mu * H - external field strength
		int latticeSize;
		int latticeSizeLessOne;
		int latticeSitesAmount; // = amount of loop single steps in one MCS
		double latticeSizeFactor; // 1 / latticeSizeAmount
		int mcsAmount; // MCS-es amount
		int repeat; // Which time the simulation is run with such parameters
		bool saveSpins;
		bool saveMeantimeQuantities;
		bool reuseSpins;
		void setT(double T);
		void setJ(int J);
		void setLatticeSize(int latticeSize);
		IsingSimulationParameters();
	public:
		IsingSimulationParameters(int J, int latticeSize, double T, double h, int mcsAmount, int repeat = 1,
			bool saveSpins = false,	bool saveMeantimeQuantities = false, bool reuseSpins = false);
		~IsingSimulationParameters();
		double getT() const;
		double getJ() const;
		double getkB() const;
		double geth() const;
		int getLatticeSize() const;
		int getRepeat() const;
		int getLastSavedSpinsConfigurationMcs() const;
	};
}