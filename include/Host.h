#ifndef HOST_H
#define HOST_H

#include <map>

struct Host 
{
	double x;
	double y;
	double reach;
	int mac;

	Host(double x, double y, double reach, int mac);
};

#endif
