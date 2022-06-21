#include "../include/Packet.h"

Packet::Packet(std::string content) : content(content) {}

void Packet::encapsulate_network_layer(int host_mac)
{
    this->hop_count = this->hop_count + 1;
    
    if (this->type == 0)
        this->path.push_back(host_mac);
}

void Packet::encapsulate_link_layer(int host_mac, int node_mac)
{
    this->mac_prev = host_mac;
    this->mac_next = node_mac;
}

void Packet::encapsulate_physical_layer()
{
    this->position = 0;
}
