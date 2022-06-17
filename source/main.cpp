#include <iostream>
#include "../include/Router.h"
#include "../include/Packet.h"
#include "../include/Host.h"
#include "../include/Simulation.h"

using namespace std;

int main()
{
	Simulation *sim = new Simulation();
	sim->read_data("../instances/a.txt");

	sim->send(0, 8, "Hello.");
	sim->wait(100);
	// std::cout << sim->is_reachable(sim->nodes[0], sim->nodes[134]) << std::endl;
	//alskjdasim->send(1, 2, "Hello there.");
	//alskjdasim->wait(100);

	delete sim;
}
