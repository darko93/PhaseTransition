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
		int getCorrelationTime();
		double getMinT();
		double getMaxT();
		bool contains(double T);
	};
}