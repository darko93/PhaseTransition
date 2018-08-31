#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		double T;
		double H;
		double M;
	public:
		IsingMeantimeQuantities(double T, double H, double M);
		~IsingMeantimeQuantities();
		static IsingMeantimeQuantities zeroes();
		double getT();
		double getH();
		double getM();
	};
}

