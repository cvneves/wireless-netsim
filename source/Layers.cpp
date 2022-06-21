#include "../include/Layers.h"

PhysicalLayerPacket::PhysicalLayerPacket() : {}

LinkLayerPacket::LinkLayerPacket() : {}

NetworkLayerPacket::NetworkLayerPacket() : {}

ApplicationLayerPacket::ApplicationLayerPacket(std::string content) : content(content) : {}