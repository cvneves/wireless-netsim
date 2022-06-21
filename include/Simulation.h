#ifndef SIMULATION_H
#define SIMULATION_H

#include "Host.h"
#include "Router.h"
#include "Packet.h"
#include "Layers.h"
#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

#define TRAVEL_SPEED 25.0
#define MAX_HOPS 40

struct Simulation 
{
	int packet_id = 1;
	int curr_time = 0;
	std::vector<Host*> nodes;
	std::vector<std::pair<int, Packet*>> events;
	std::vector<std::vector<double>> distance;
	std::string instance_file_name;
	std::set<std::pair<int, int>> edge_list;
	std::map<std::pair<int, int>, Packet*> arcs;

	std::vector<std::vector<int>> neighbors;
	void read_data(std::string file_name);

	void update();

	void log_curr_state();

	double get_distance(int from, int to);

	bool is_reachable(int from, int to);

	int get_travel_time(int from, int to);

	void send(int mac_source, int mac_destination, std::string content);

	void cast(int mac);

	void wait(int wait_time);

	void update_packet_position(Packet *packet);

	~Simulation();
};

#endif
