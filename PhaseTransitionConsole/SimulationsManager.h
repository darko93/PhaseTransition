#pragma once

#include "INotifier.h"
#include "IIsingInputData.h"

namespace pht = PhaseTransition;

class SimulationsManager
{
private:
	const INotifier* notifier;
public:
	SimulationsManager(const INotifier& notifier);
	~SimulationsManager();
	void performAllSimulations() const;
};

