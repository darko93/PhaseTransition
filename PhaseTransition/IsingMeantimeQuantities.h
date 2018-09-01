#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		double T;
		double H;
		int M;
	public:
		IsingMeantimeQuantities(double T, double H, int M);
		~IsingMeantimeQuantities();
		static IsingMeantimeQuantities zeroes();
		double getT();
		double getH();
		int getM();
	};
}

