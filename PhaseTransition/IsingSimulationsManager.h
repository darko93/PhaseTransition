#pragma once

#include "IsingModel.h"
#include "IIsingInputData.h"

namespace PhaseTransition
{
	class IsingSimulationsManager
	{
	private:
		IsingModel* isingModel;
	public:
		IsingSimulationsManager(IsingModel* isingModel);
		~IsingSimulationsManager();
		void performAllSimulations(IIsingInputData* isingInputData);
	};
}