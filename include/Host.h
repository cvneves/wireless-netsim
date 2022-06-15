#ifndef HOST_H
#define HOST_H

#include "Packet.h"

class Host 
{
	double x;
	double y;
	double reach;
	int mac;

	public:
		void send(Packet *p, int destination_mac);
		void listen();
};

#endif
