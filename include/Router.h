#ifndef ROUTER_H
#define ROUTER_H

#include "Host.h"
#include <vector>

class Router: public Host
{
	std::vector<std::vector<int>> route_table;

	public:
		Router(double x, double y, double reach, int mac) : Host(x, y, reach, mac) {}
};

#endif
