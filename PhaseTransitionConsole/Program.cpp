#include <iostream>
#include "SimulationsManager.h"
#include "Notifier.h"

int main()
{	
	//std::cout << system("cd");
	Notifier notifier;
	SimulationsManager simulationsManager(notifier);
	simulationsManager.performAllSimulations();
	std::cin.get();
	return 0;
}