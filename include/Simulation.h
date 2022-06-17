#ifndef SIMULATION_H
#define SIMULATION_H

#include "Host.h"
#include "Router.h"
#include "Packet.h"
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

#define TRAVEL_SPEED 5000.0

struct Simulation 
{
	int curr_time = 0;
	std::vector<Host*> nodes;
	std::vector<std::pair<int, Packet*>> events;
	std::vector<std::vector<double>> distance;
	std::string instance_file_name;
	std::set<std::pair<int, int>> edge_list;

	void cast(int mac, Packet *p);

	void read_data(std::string file_name);

	void update();

	void log_curr_state();

	double get_distance(Host *host_a, Host *host_b);

	bool is_reachable(Host *host_from, Host *host_to);

	int get_travel_time(Host *host_a, Host *host_b);

	void send(int mac_source, int mac_destination, std::string content);

	void cast(Host *host, Packet *packet);

	void wait(int wait_time);

	~Simulation();
};

#endif
