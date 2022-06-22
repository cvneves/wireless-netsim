#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

struct Packet 
{
	// Application Layer
	std::string content;
	
	// Network Layer
	int hop_count = 0;
	std::vector<int> path;
	int cursor;

	// Link Layer
	int mac_source;
	int mac_destination;
	int mac_prev = -1;
	int mac_next = -1;
	int mac_next_hop = -1;

	// Physical Layer
	int id;
	int type = 0; // 0 = request | 1 = reply
	double position = 0;

	Packet(std::string content);

	void encapsulate_network_layer(int host_mac);
	void encapsulate_link_layer(int host_mac, int node_mac);
	void encapsulate_physical_layer();
};

#endif
