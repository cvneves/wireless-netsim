#include "../include/Simulation.h"

Simulation::~Simulation()
{
	while (!events.empty())
	{
		delete events.top().second;
		events.pop();
	}

	for (const auto &node : nodes)
	{
		delete node;
	}
}

void Simulation::update()
{


	curr_time++;
}

void Simulation::log_curr_state()
{

}

void Simulation::read_data(std::string file_name)
{
	std::ifstream file;

	file.open(file_name);

	std::string line;
	int i = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::stringstream s(line);
			std::string temp;
			double x, y, reach;
			Router *router = new Router(x, y, reach, i);
			nodes.push_back(router);
			i++;
		}
		file.close();
	}
}

double Simulation::get_distance(Host *host_from, Host *host_to)
{
	return sqrt(
			pow(host_from->x - host_to->x, 2) 
			+ pow(host_from->y - host_to->y, 2)
			);
}

bool Simulation::is_reachable(Host *host_from, Host *host_to)
{
	return get_distance(host_from, host_to) <= host_to->reach;
}

int Simulation::get_travel_time(Host *host_a, Host *host_b)
{
	return std::floor(get_distance(host_a, host_b) / TRAVEL_SPEED);
}

void Simulation::send(
		int mac_source, 
		int mac_destination, 
		std::string content
		)
{
	Packet *packet = new Packet(content);
	packet->mac_source = mac_source;
	packet->mac_destination = mac_destination;
	cast(
			nodes[mac_source], 
			packet
			);
}

void Simulation::cast(Host *host, Packet *packet)
{
	for (const auto &node : nodes)
	{
		if (is_reachable(host, node))
		{
			Packet *packet_copy = new Packet("");
			*packet_copy = *packet;
			packet_copy->next_host = node;

			int arrival_time = curr_time 
				+	get_travel_time(host, node);

			events.push({arrival_time, packet_copy});
		}
	}
}

void Simulation::wait(int wait_time)
{

}
