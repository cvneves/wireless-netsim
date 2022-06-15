#ifndef SIMULATION_H
#define SIMULATION_H

#include "Host.h"
#include "Router.h"
#include <queue>

class Event
{

};

class Simulation 
{
	int time = 0;
	std::vector<Host*> entities;
	std::priority_queue<Event*> events;
	std::vector<std::vector<double>> distance;

	public:
		void update();
		void log_curr_state();
		bool reachable(Host *h1, Host *h2);
};

#endif
