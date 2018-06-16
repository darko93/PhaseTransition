#include "CorrelationTime.h"

namespace PhaseTransition
{
	CorrelationTime::CorrelationTime(int correlationTime, double minT, double maxT)
		: correlationTime(correlationTime), minT(minT), maxT(maxT)
	{
	}

	CorrelationTime::~CorrelationTime()
	{
	}

	int CorrelationTime::getCorrelationTime()
	{
		return this->correlationTime;
	}

	double CorrelationTime::getMinT()
	{
		return this->minT;
	}

	double CorrelationTime::getMaxT()
	{
		return this->maxT;
	}

	bool CorrelationTime::contains(double T)
	{
		return this->minT <= T && T < this->maxT;
	}
}