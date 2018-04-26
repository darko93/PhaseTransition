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
}