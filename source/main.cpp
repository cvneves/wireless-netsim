#include <iostream>
#include "../include/Router.h"
#include "../include/Packet.h"
#include "../include/Host.h"
#include "../include/Simulation.h"

using namespace std;

int main()
{
	Simulation *simulation = new Simulation();
	simulation->read_data("../instances/a.txt");
}
