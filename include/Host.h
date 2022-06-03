#ifndef HOST_H
#define HOST_H

#include "Packet.h"

class Host 
{
	double x;
	double y;
	double reach;
	long long int mac;
	bool send(Packet *p, Host *h);
};

#endif
