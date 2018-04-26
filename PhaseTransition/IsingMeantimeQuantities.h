#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		double T;
		double H;
		double H2;
		double M;
		double M2;
	public:
		IsingMeantimeQuantities(double T, double H, double H2, double M, double M2);
		~IsingMeantimeQuantities();
		double getT();
		double getH();
		double getH2();
		double getM();
		double getM2();
	};
}

