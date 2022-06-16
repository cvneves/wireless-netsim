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
		Host(double x, double y, double reach, int mac) : x(x), y(y), reach(reach), mac(mac) {}
		void cast(Host *h, Packet *p);
};

#endif
