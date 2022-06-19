#ifndef HOST_H
#define HOST_H

#include "Packet.h"
#include <map>
#include <queue>

struct Host 
{
	double x;
	double y;
	double reach;
	int mac;
	bool busy_tone = false;
	std::queue<Packet*> buffer;

	Host(double x, double y, double reach, int mac);
};

#endif
