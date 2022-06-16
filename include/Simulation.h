#ifndef SIMULATION_H
#define SIMULATION_H

#include "Host.h"
#include "Router.h"
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class Simulation 
{
	int time = 0;
	std::vector<Host*> entities;
	std::priority_queue<std::pair<int, Packet*>> packets;
	std::vector<std::vector<double>> distance;

	public:
		void read_data(std::string file_name);

		void update();
		void log_curr_state();

		bool reachable(Host *host_a, Host *host_b);
};

#endif
