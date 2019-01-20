#pragma once

namespace PhaseTransition
{
	class IsingMeantimeQuantities
	{
		int E;
		int M;
	public:
		IsingMeantimeQuantities(int E, int M);
		~IsingMeantimeQuantities();
		static IsingMeantimeQuantities zeroes();
		int getE() const;
		int getM() const;
	};
}

