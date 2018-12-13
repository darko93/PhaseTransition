#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		double E;
		double M;
	public:
		IsingMeantimeQuantities(double E, double M);
		~IsingMeantimeQuantities();
		static IsingMeantimeQuantities zeroes();
		double getE() const;
		double getM() const;
	};
}

