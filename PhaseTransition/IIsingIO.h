#pragma once

#include<iostream>

#include "IIsingInputData.h"
#include "IsingMeantimeQuantities.h"

class IsingModel;

namespace PhaseTransition
{
	class IIsingIO
	{
	public:
		virtual ~IIsingIO() {};
		virtual void saveSpins(const IsingModel& isingModel, int mcs) const = 0;
		virtual void saveMeantimeQuantities(const IsingMeantimeQuantities& meantimeQuantities, const IsingSimulationParameters& simParams, int mcs) const = 0;
	};
}