#ifndef HOST_H
#define HOST_H

#include "Packet.h"
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
	std::queue<Packet*> buffer;
	std::set<int> packet_ids;
	std::map<int, int> routing_table; // nó de destino | próximo pulo

	Host(double x, double y, double reach, int mac);
};

#endif
