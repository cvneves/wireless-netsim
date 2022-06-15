#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

class Packet 
{
	int type;
	int mac_source;
	int mac_destination;
	std::string content;
	std::vector<int> path;
};

#endif
