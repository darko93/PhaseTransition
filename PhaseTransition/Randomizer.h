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
		int randomNr(int max) const;
		double randomNrBetween0And1() const;
		double randomNr(double min, double max) const;
	};
}