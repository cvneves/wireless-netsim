#ifndef ROUTER_H
#define ROUTER_H

#include "Host.h"
#include <vector>

struct Router: public Host
{
	std::vector<std::vector<int>> route_table;

	Router(double x, double y, double reach, int mac) : Host(x, y, reach, mac) {}
};

#endif
