#pragma once

#include<iostream>

class IIsingInputData
{
public:
	virtual ~IIsingInputData() {};
	virtual double getJ() = 0;
	virtual int getLatticeSize() = 0;
	virtual double geth() = 0;
	virtual double getMinT() = 0;
	virtual double getMaxT() = 0;
	virtual double getTStep() = 0;
	virtual int getTRepeats() = 0;
	virtual std::string getResultsFilePath() = 0;
	virtual std::string getSpinsFilePath() = 0;
	virtual bool getSaveMeantimeQuanities() = 0;
	virtual int getSavingMeantimeQuantitiesInterval() = 0;
	virtual std::string getMeantimeQuantitiesFilePathPattern() = 0;
};

