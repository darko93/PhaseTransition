#pragma once

#include "INotifier.h"
#include "IsingSimulationParameters.h"

namespace pht = PhaseTransition;

class Notifier : public INotifier
{
public:
	Notifier();
	~Notifier();
	void notifyConstSimParams(const pht::IsingSimulationParameters& simParams) const override;
	void notifyMutableSimParams(const pht::IsingSimulationParameters& simParams) const override;
	void notifyFinishedSimulations() const override;
};

