#include <iostream>
#include "Notifier.h"

Notifier::Notifier()
{
}


Notifier::~Notifier()
{
}

void Notifier::notifyConstSimParams(const pht::IsingSimulationParameters& simParams) const
{
	std::cout << "kB=" << simParams.getkB() << std::endl << "J=" << simParams.getJ() << std::endl << std::endl;
}

void Notifier::notifyMutableSimParams(const pht::IsingSimulationParameters& simParams) const
{
	std::cout << "latticeSize=" << simParams.getLatticeSize() << "\t" << "T=" << simParams.getT()
		<< "\t" << "h=" << simParams.geth() << "\t" << "repeat=" << simParams.getRepeat() << std::endl;
}

void Notifier::notifyFinishedSimulations() const
{
	std::cout << "Finished!" << std::endl;
}
