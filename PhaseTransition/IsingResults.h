#pragma once

namespace PhaseTransition
{
	class IsingResults
	{
		friend class IsingModel;
	private:
		double T;
		double M; // net magnetization per site
		double U; // internal energy per site
		double Cv; // heat capacity per site
		double X; // magnetic susceptibiilty per site
	public:
		IsingResults(double T, double M, double U, double Cv, double X);
		IsingResults(double T, double U, double Cv, double X);
		~IsingResults();
		double getT();
		double getM();
		double getU();
		double getCv();
		double getX();
	};
}