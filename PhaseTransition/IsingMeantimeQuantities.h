#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		double H;
		int M;
	public:
		IsingMeantimeQuantities(double H, int M);
		~IsingMeantimeQuantities();
		static IsingMeantimeQuantities zeroes();
		double getH();
		int getM();
	};
}

