#ifndef HOST_H
#define HOST_H

#include "Layers.h"
#include <map>
#include <set>
#include <queue>

struct Host 
{
	double x;
	double y;
	double reach;
	int mac;
	bool busy_tone = false;
	std::queue<PhysicalLayerPacket*> buffer;
	std::set<int> packet_ids;
	std::map<int, int> routing_table;

	Host(double x, double y, double reach, int mac);
};

#endif
