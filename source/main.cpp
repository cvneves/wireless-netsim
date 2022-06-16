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

	sim->send(0, 1, "Hello.");
	sim->wait(100);
	sim->send(1, 2, "Hello there.");
	sim->wait(100);

	delete sim;
}
