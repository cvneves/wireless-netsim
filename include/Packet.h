#ifndef PACKET_H
#define PACKET_H

#include "Host.h"
#include <string>
#include <vector>

struct Packet 
{
	int type; // 0 = send,
						// 1 = confirmation
	int mac_source;
	int mac_destination;
	int hop_count = 0;
	Host *next_host = NULL;
	std::string content;
	std::vector<int> path;

	Packet(std::string content);
};

#endif
