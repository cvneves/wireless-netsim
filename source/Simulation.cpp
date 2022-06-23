#include "../include/Simulation.h"

Simulation::~Simulation()
{
	log_geral.close();
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

Simulation::Simulation()
{
}

void Simulation::update_node(int mac)
{
	Host *host = nodes[mac];

	if (host->buffer.empty())
		return;

	Packet *packet = host->buffer.front();

	if (packet->hop_count > MAX_HOPS || host->packet_ids.find(packet->id) != host->packet_ids.end())
	{
		delete packet;
		host->buffer.pop();
		return;
	}

	host->packet_ids.insert(packet->id);

	bool its_casting_time = true;

	if (packet->type == 0)
	{
		if (packet->mac_next_hop != -1 && packet->mac_next_hop != packet->mac_next)
		{

			its_casting_time = false;
		}

		if (host->routing_table.find(packet->mac_destination) !=
			host->routing_table.end())
		{
			packet->mac_next_hop = host->routing_table[packet->mac_destination];
		}
	}

	if (packet->type == 0 && packet->mac_next == packet->mac_destination)
	{

		std::ofstream log;
		log.open("../log/log.txt", std::ofstream::app);

		log << "Pacote com conteúdo \"" << packet->content << "\" chegou a seu destino final, nó " << packet->mac_destination << "." << std::endl; 

		packet->type = 1;		 // reply
		packet->content = "ACK"; // aknowledgement
		packet->id = std::min(-packet->id, packet->id);
		packet->hop_count = 0;
		packet->path.push_back(packet->mac_next);
		packet->cursor = packet->path.size() - 1;

		log << "Caminho percorrido pelo pacote: ";
		for (int i = 0; i < packet->path.size(); i++)
		{
			log << packet->path[i];
			if(i < packet->path.size() - 1) log << "->";
		}
		log << std::endl;

		log.close();
		
	}

	if (packet->type == 1)
	{
		if (host->mac == packet->path[packet->cursor])
		{
			fill_routing_table(packet);
			if (packet->cursor != 0)
				packet->cursor--;
		}
		else
		{
			its_casting_time = false;
		}
	}

	if (host->mac == packet->mac_source && packet->type == 1)
		its_casting_time = false;

	if (its_casting_time)
		cast(host->mac, packet);

	delete packet;
	host->buffer.pop();
}

bool Simulation::has_busy_neighbor(int mac)
{
	for (const auto &mac_neighbor : neighbors[mac])
	{
		Host *node = nodes[mac_neighbor];
		if (node->busy_tone)
			return true;
	}

	return false;
}

void Simulation::update()
{
	log_curr_state();

	// every packet traveling between two
	// nodes must have its position after
	// each update
	for (auto arc : arcs)
	{
		Packet *packet = arc.second;
		if (arc.second)
			update_packet_position(packet);
	}

	for (const auto &node : nodes)
	{
		// if there is at least one
		// busy neighbor, do nothing
		if (has_busy_neighbor(node->mac))
			continue;

		update_node(node->mac);
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
			temp_file << arc.first.first << " " << arc.first.second << " " << -1 << " " << 0 << std::endl;
		}
		else
		{
			temp_file << arc.first.first << " " << arc.first.second << " " << arc.second->position << " " << arc.second->type << std::endl;
		}
	}

	temp_file.close();
}

void Simulation::logar_estado()
{
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
			Host *host = new Host(x, y, reach, i);
			nodes.push_back(host);
			i++;
		}
		file.close();
	}

	neighbors = std::vector<std::vector<int>>(nodes.size());
	for (const auto &host_a : nodes)
	{
		for (const auto &host_b : nodes)
		{
			if (host_a != host_b && is_reachable(host_a->mac, host_b->mac))
			{
				neighbors[host_a->mac].push_back(host_b->mac);
			}
		}
	}
}

double Simulation::get_distance(int from, int to)
{
	return sqrt(
		pow(nodes[from]->x - nodes[to]->x, 2) + pow(nodes[from]->y - nodes[to]->y, 2));
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
	std::string content)
{
	Packet *packet = new Packet(content);
	packet->mac_source = mac_source;
	packet->mac_destination = mac_destination;
	packet->id = packet_id++;
	nodes[mac_source]->buffer.push(packet);

	// cast(mac_source);
}

void Simulation::cast(int mac, Packet *packet)
{
	Host *host = nodes[mac];

	std::ofstream log;
	log.open("../log/log.txt", std::ofstream::app);

	if (packet->type == 0)
	{
		log << "Nó " << mac << " realizando transmissão do pacote com conteúdo \"" << packet->content << "\"." << std::endl;
	}
	else
	{
		log << "Nó " << mac << " realizando transmissão da resposta de recebimento do pacote. Próximo nó do caminho: " << packet->path[packet->cursor] << std::endl;
	}

	for (const auto &neighbor : neighbors[mac])
	{
		Host *node = nodes[neighbor];
		Packet *packet_copy = new Packet("");
		*packet_copy = *packet;

		packet_copy->encapsulate_network_layer(host->mac);
		packet_copy->encapsulate_link_layer(host->mac, node->mac);
		packet_copy->encapsulate_physical_layer();

		node->busy_tone = true;

		arcs[{host->mac, node->mac}] = packet_copy;
	}

	log.close();

	// std::cout << packet->hop_count << " " << packet << std::endl;
}

void Simulation::wait(int wait_time)
{
	std::ofstream log;
	log.open("../log/log.txt", std::ofstream::app);

	for (int i = 0; i < wait_time; i++)
	{

		log << std::endl
			<< "Tempo: " << curr_time << std::endl;
		update();
	}

	log.close();
}

void Simulation::update_packet_position(Packet *packet)
{
	packet->position += TRAVEL_SPEED / get_distance(packet->mac_prev, packet->mac_next) / packet->content.size();
	packet->position = std::min(packet->position, 1.0);

	if (packet->position == 1.0)
	{
		std::ofstream log;
		log.open("../log/log.txt", std::ofstream::app);

		if(packet->type == 1 && packet->mac_next == packet->mac_source) log << "Resposta de recebimento do pacote chegou ao nó " << packet->mac_next << "." << std::endl;
		log << "Pacote vindo do nó " << packet->mac_prev << " com conteúdo \"" << packet->content << "\" chegou no nó " << packet->mac_next << "." << std::endl;

		arcs[{packet->mac_prev, packet->mac_next}] = NULL;
		nodes[packet->mac_next]->buffer.push(packet);
		nodes[packet->mac_next]->busy_tone = false;
		log.close();
	}
}

void Simulation::fill_routing_table(Packet *packet)
{
	Host *host = nodes[packet->mac_next];
	// std::cout << "Host " << host->mac << std::endl;
	for (int i = packet->cursor + 1; i < packet->path.size(); i++)
	{
		// std::cout << packet->path[i] << " " << packet->path[packet->cursor + 1] << std::endl;
		host->routing_table[packet->path[i]] = packet->path[packet->cursor + 1];
	}
}
