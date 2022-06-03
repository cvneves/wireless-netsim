#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

class Packet 
{
	int type;
	long long int mac_originator;
	long long int mac_destination;
	std::string content;
	vector<long long int> path;
};

#endif
