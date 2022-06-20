#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

struct Packet 
{
	int type = 0; // 0 = request,
			      // 1 = reply
	int mac_source;
	int mac_destination;
	int hop_count = 0;
	int mac_prev = -1;
	int mac_next = -1;
	std::string content;
	std::vector<int> path;
	double position = 0;
	int id;
	int cursor;

	Packet(std::string content);
};

#endif
