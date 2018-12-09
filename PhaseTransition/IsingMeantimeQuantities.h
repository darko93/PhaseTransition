#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		double E;
		int M;
	public:
		IsingMeantimeQuantities(double E, int M);
		~IsingMeantimeQuantities();
		static IsingMeantimeQuantities zeroes();
		double getE() const;
		int getM() const;
	};
}

