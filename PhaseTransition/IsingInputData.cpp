#include "IsingInputData.h"

namespace PhaseTransitionIO
{
	IsingInputData::IsingInputData(int J, int latticeSize, double h, double minT, double maxT, double ktStep,
		int TRepeats, std::string resultsFilePath, std::string spinsFilePath)
		: J(J), latticeSize(latticeSize), h(h), minT(minT), maxT(maxT), TStep(ktStep),
		  TRepeats(TRepeats), resultsFilePath(resultsFilePath), spinsFilePath(spinsFilePath)
	{
	}

	IsingInputData::~IsingInputData()
	{
	}

	double IsingInputData::getJ()
	{
		return this->J;
	}

	double IsingInputData::geth()
	{
		return this->h;
	}

	int IsingInputData::getLatticeSize()
	{
		return this->latticeSize;
	}

	double IsingInputData::getMinT()
	{
		return this->minT;
	}

	double IsingInputData::getMaxT()
	{
		return this->maxT;
	}

	double IsingInputData::getTStep()
	{
		return this->TStep;
	}

	int IsingInputData::getTRepeats()
	{
		return this->TRepeats;
	}

	std::string IsingInputData::getResultsFilePath()
	{
		return this->resultsFilePath;
	}

	std::string IsingInputData::getSpinsFilePath()
	{
		return this->spinsFilePath;
	}
}