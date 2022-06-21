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

	std::vector<bool> ready(nodes.size(), false);

	for (auto arc : arcs)
	{
		Packet *packet = arc.second;
		if (arc.second)
			update_packet_position(packet);
	}

	for (const auto &node : nodes)
	{
		bool busy = false;
		for (const auto &neighbor : neighbors[node->mac])
		{
			Host *node = nodes[neighbor];
			if (node->busy_tone)
			{
				busy = true;
				break;
			}
		}
		
		if (!busy)
		{
			if (!node->buffer.empty() && node->buffer.front()->type == 0)
			{
				cast(node->mac);		
			}	
			else if (!node->buffer.empty()
				&& node->mac == node->buffer.front()->path[node->buffer.front()->cursor]
				&& node->buffer.front()->cursor != 0)  // Checks if
   			{
				node->buffer.front()->cursor--;
				cast(node->mac);
			}
		}

	}

	curr_time++;
}

void Simulation::log_curr_state()
{
	std::ofstream temp_file;
	temp_file.open("../output/temp" + std::to_string(10000000 + curr_time) + ".txt");

	for (const auto &arc : arcs)
	{
		if (arc.second == NULL)
		{
			temp_file << arc.first.first << 
			" " << arc.first.second << 
			" " << -1 << " " << 0 << std::endl;
		} else {
			temp_file << arc.first.first << 
			" " << arc.first.second << 
			" " << arc.second->position <<
			" " << arc.second->type << std::endl;
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

	neighbors = std::vector<std::vector<int>> (nodes.size());
	for (const auto &host_a : nodes)
	{
		for (const auto &host_b : nodes)
		{
			if (host_a != host_b
					&& is_reachable(host_a->mac, host_b->mac))
			{
				neighbors[host_a->mac].push_back(host_b->mac);
			}
		}
	}
}

double Simulation::get_distance(int from, int to)
{
	return sqrt(
			pow(nodes[from]->x - nodes[to]->x, 2) 
			+ pow(nodes[from]->y - nodes[to]->y, 2)
			);
}

bool Simulation::is_reachable(int from, int to)
{
	return get_distance(from, to) <= nodes[from]->reach;
}

int Simulation::get_travel_time(int from, int to)
{
	return std::ceil(get_distance(from, to) / TRAVEL_SPEED);
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
	packet->id = packet_id++;
	nodes[mac_source]->buffer.push(packet);

	cast(mac_source);
}

void Simulation::cast(int mac)
{
	Host *host = nodes[mac];
	if (host->buffer.empty())
		return;

	Packet *packet = host->buffer.front();

	if (host->packet_ids.find(packet->id) != host->packet_ids.end())
	{
		delete packet;
		host->buffer.pop();

		return;
	}
	else {
		host->packet_ids.insert(packet->id);
	}

	bool flag = false;

	for (const auto &neighbor : neighbors[mac])
	{
		Host *node = nodes[neighbor];
		if (node != host
				&& packet->hop_count <= MAX_HOPS)
		{
			flag = true;
			Packet *packet_copy = new Packet("");
			*packet_copy = *packet;
			packet_copy->hop_count = packet_copy->hop_count + 1;
			
			if(packet_copy->type == 0)
				packet_copy->path.push_back(host->mac);
			
			packet_copy->mac_prev = host->mac;
			packet_copy->mac_next = node->mac;
			packet_copy->position = 0;

			node->busy_tone = true;

			arcs[{host->mac, node->mac}] = packet_copy;
		}
		if (flag && node != host)
		{
			node->busy_tone = true;
		}
	}

	std::cout << packet->hop_count << " " << packet << std::endl;
	delete packet;
	host->buffer.pop();
}

void Simulation::wait(int wait_time)
{
	for (int i = 0; i < wait_time; i++)
	{
		update();
	}
}

void Simulation::update_packet_position(Packet *packet)
{
	packet->position += TRAVEL_SPEED / get_distance(
			packet->mac_prev,
			packet->mac_next
			) / packet->content.size();
	packet->position = std::min(packet->position, 1.0); 

	if (packet->position == 1.0)
	{
		if (packet->mac_next == packet->mac_destination)
		{
			packet->type = 1; // reply
			packet->content = "ACK"; // aknowledgement
			packet->id = std::min(-packet->id, packet->id);
			packet->hop_count = 0;
			packet->path.push_back(packet->mac_next);
			packet->cursor = packet->path.size() - 1;
		}

		// 0 -> 1 -> 2 -> 3 -> 4

		nodes[packet->mac_next]->buffer.push(packet);
		nodes[packet->mac_next]->busy_tone = false;
		arcs[{packet->mac_prev, packet->mac_next}] = NULL;
	}
}
