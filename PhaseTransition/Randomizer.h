#pragma once

#include <random>

namespace PhaseTransition
{
	class Randomizer
	{
#pragma region Singleton
	private:
		Randomizer();
	public:
		static Randomizer& getInstance()
		{
			static Randomizer instance; // Guaranteed to be destroyed; Instantiated on first use.
			return instance;
		}
		Randomizer(Randomizer const&) = delete;
		void operator=(Randomizer const&) = delete;
#pragma endregion
	private:
		std::mt19937_64 mt;
		std::uniform_int_distribution<int> intDist;
		std::uniform_real_distribution<double> realDist;
	public:
		void setMaxRandomIntNr(int max);
		int randomIntNr() const;
		double randomNrBetween0And1() const;
	};
}