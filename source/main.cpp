#include <iostream>
#include "../include/Router.h"
#include "../include/Packet.h"
#include "../include/Host.h"
#include "../include/Simulation.h"

using namespace std;

int main(int argc, char **argv)
{
	Simulation *sim = new Simulation();
	sim->read_data(std::string(argv[1]));

	// for (int i = 0; i < sim->nodes.size(); i++)
	// {
	// 	sim->nodes[i]->reach = 20;
	// }

	sim->send(0, 1, "Hello there.");
	sim->wait(500);
	// std::cout << sim->is_reachable(sim->nodes[0], sim->nodes[134]) << std::endl;
	//alskjdasim->send(1, 2, "Hello there.");
	//alskjdasim->wait(100);

	delete sim;
}
