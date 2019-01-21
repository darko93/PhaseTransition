#pragma once

namespace PhaseTransition
{
	class IsingSimulationParameters
	{
		friend class IsingModel;
		friend class IIsingInputData;
	private:
		double kB = 1; // Boltzman constant
		int J; // coupling strength, +1 - ferromagnetic, -1 - antiferromagnetic
		double T;
		double beta; // 1/T
		double h; // mu * H - external field strength
		int L;
		int LLessOne;
		int N; // lattice sites amount = amount of loop Metropolis steps in one MCS
		double LFactor; // 1 / LAmount
		int mcsAmount; // MCS-es amount
		int repeat; // Which time the simulation is run with such parameters
		bool saveSpins;
		bool saveMeantimeQuantities;
		bool reuseSpins;
		void setT(double T);
		void setJ(int J);
		void setL(int L);
	public:
		static IsingSimulationParameters getDefault();
		IsingSimulationParameters(int J, int L, double T, double h, int mcsAmount, int repeat = 1,
			bool saveSpins = false,	bool saveMeantimeQuantities = false, bool reuseSpins = false);
		~IsingSimulationParameters();
		double getT() const;
		int getJ() const;
		double getkB() const;
		double geth() const;
		int getL() const;
		int getMcsAmount() const;
		int getRepeat() const;
	};
}