#pragma once

#include "IsingSimulationParameters.h"

namespace pht = PhaseTransition;

class INotifier
{
public:
	virtual ~INotifier() {};
	virtual void notifyConstSimParams(const pht::IsingSimulationParameters& simParams) const = 0;
	virtual void notifyMutableSimParams(const pht::IsingSimulationParameters& simParams) const = 0;
	virtual void notifyFinishedSimulations() const = 0;
};

