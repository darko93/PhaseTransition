#pragma once
namespace PhaseTransition
{
	class CorrelationTime
	{
	private:
		int correlationTime;
		double minT;
		double maxT;
	public:
		CorrelationTime(int correlationTime, double minT, double maxT);
		~CorrelationTime();
	};
}