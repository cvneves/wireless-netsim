#ifndef LAYERS_H
#define LAYERS_H

#include <string>
#include <vector>

struct NetworkLayerPacket;
struct ApplicationLayerPacket;
struct LinkLayerPacket;

struct ApplicationLayerPacket
{
	std::string content;

	ApplicationLayerPacket(std::string content);
};

struct NetworkLayerPacket : public ApplicationLayer // Rede
{
	std::vector<int> path;
	int hop_count = 0;
	int cursor;
	double position = 0;

	NetworkLayerPacket();
};


struct LinkLayerPacket : public NetworkLayerPacket // Enlace
{
	int mac_source;
	int mac_destination;
	int mac_prev = -1;
	int mac_next = -1;

	LinkLayerPacket();
};

struct PhysicalLayerPacket : public LinkLayerPacket
{
	int type = 0; // 0 = request,
			      // 1 = reply
	int id;

	PhysicalLayerPacketPacket();
};



#endif
