#include "IsingMeantimeQuantities.h"



IsingMeantimeQuantities::IsingMeantimeQuantities(double H, double H2, double M, double M2)
	: H(H), H2(H2), M(M), M2(M2)
{
}

IsingMeantimeQuantities::~IsingMeantimeQuantities()
{
}

double IsingMeantimeQuantities::getH()
{
	return this->H;
}

double IsingMeantimeQuantities::getH2()
{
	return this->H2;
}

double IsingMeantimeQuantities::getM()
{
	return this->M;
}

double IsingMeantimeQuantities::getM2()
{
	return this->M2;
}
