#include <iostream>
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

	sim->send(0, 5, "Hello there.");
	sim->wait(200);
	sim->send(0, 5, "Hello there.");
	sim->wait(200);

	// sim->send(0, 5, "Hello there.");
	// sim->wait(100);
	for (auto &host : sim->nodes)
	{
		std::cout << "Host " << host->mac << std::endl; 
		for (auto &tab : host->routing_table)
		{
			std::cout << tab.first << " " << tab.second << std::endl;
		}
	}
	// std::cout << sim->is_reachable(sim->nodes[0], sim->nodes[134]) << std::endl;
	//alskjdasim->send(1, 2, "Hello there.");
	//alskjdasim->wait(100);

	delete sim;
}
