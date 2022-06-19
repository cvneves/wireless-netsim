#include "../include/Simulation.h"

Simulation::~Simulation()
{
	while (!events.empty())
	{
		delete events.back().second;
		events.pop_back();
	}

	for (const auto &node : nodes)
	{
		delete node;
	}
}

void Simulation::update()
{
	log_curr_state();

	for (auto &domain : domains)
	{
		if (domain.second.size() > 1)
		{
			domain.second.clear();
			continue;
		}

		for (auto &packet : domain.second)
		{
			packet->position += TRAVEL_SPEED / get_distance(
					packet->prev_host,
					packet->next_host
					) / packet->content.size();
			packet->position = std::min(packet->position, 1.0); 

			if (packet->position == 1.0)
			{
				cast(packet->next_host, packet);
				delete packet;
				packet = NULL;
			}
		}

		auto remove_it = std::remove_if(
				domain.second.begin(), 
				domain.second.end(), 
				[&](const Packet* packet){return packet == NULL;}
				);
		domain.second.erase(remove_it, domain.second.end());
	}

	curr_time++;
}

void Simulation::log_curr_state()
{
	std::ofstream temp_file;
	temp_file.open("../output/temp" + std::to_string(10000000 + curr_time) + ".txt");

	for (const auto &domain : domains)
	{
		if (domain.second.empty())
		{
			temp_file << domain.first.first << 
			" " << domain.first.second << 
			" " << -1 << std::endl;
		}

		for (const auto &packet : domain.second)
		{
			temp_file << domain.first.first << 
			" " << domain.first.second << 
			" " << packet->position << std::endl;
		}
	}

	temp_file.close();
}

void Simulation::read_data(std::string file_name)
{
	instance_file_name = file_name;
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
			s >> x;
			s >> y;
			s >> reach;
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
	return std::ceil(get_distance(host_a, host_b) / TRAVEL_SPEED);
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

	cast(nodes[mac_source], packet);
}

void Simulation::cast(Host *host, Packet *packet)
{
	for (const auto &node : nodes)
	{
		if (node != host
				&& is_reachable(host, node) 
				&& node != packet->prev_host
				&& packet->hop_count <= MAX_HOPS)
		{
			Packet *packet_copy = new Packet("");
			*packet_copy = *packet;
			packet_copy->hop_count = packet->hop_count + 1;
			packet_copy->prev_host = host;
			packet_copy->next_host = node;
			packet_copy->position = 0;

			std::pair temp = {host->mac, node->mac};
			domains[temp].push_back(packet_copy);

			// int arrival_time = curr_time 
			// 	+	get_travel_time(host, node);

			// events.push_back({-arrival_time, packet_copy});
			// push_heap(events.begin(), events.end());
		}
	}
}

void Simulation::wait(int wait_time)
{
	for (int i = 0; i < wait_time; i++)
	{
		update();
	}
}
