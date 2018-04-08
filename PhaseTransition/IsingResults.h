#pragma once

namespace PhaseTransition
{
	class IsingResults
	{
		friend class IsingModel;
	private:
		double T;
		double U; // internal energy per site
		double Cv; // heat capacity per site
		double M; // net magnetization per site
		double X; // magnetic susceptibiilty per site
	public:
		IsingResults(double T, double U, double Cv, double M, double X);
		~IsingResults();
		double getT();
		double getU();
		double getCv();
		double getM();
		double getX();
	};
}