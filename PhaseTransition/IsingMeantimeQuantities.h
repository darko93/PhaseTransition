#pragma once
class IsingMeantimeQuantities
{
	double H;
	double H2;
	double M;
	double M2;
public:
	IsingMeantimeQuantities(double H, double H2, double M, double M2);
	~IsingMeantimeQuantities();
	double getH();
	double getH2();
	double getM();
	double getM2();
};

