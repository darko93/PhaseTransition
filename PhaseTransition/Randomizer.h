#pragma once

namespace PhaseTransition
{
	class Randomizer
	{
#pragma region Singleton
	public:
		static Randomizer& getInstance()
		{
			static Randomizer instance; // Guaranteed to be destroyed; Instantiated on first use.
			return instance;
		}
		Randomizer(Randomizer const&) = delete;
		void operator=(Randomizer const&) = delete;
	private:
		Randomizer() { }
#pragma endregion

	public:
		double randomNrBetween0And1();
		double randomNr(double min, double max);
	};
}