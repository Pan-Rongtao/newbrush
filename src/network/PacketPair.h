#pragma once
#include "Packet.h"

namespace nb{ namespace Network{

struct PacketPair
{
	PacketPair(Packet *request, Packet *ack) : Request(request), Ack(ack) {}
	Packet	*Request;
	Packet	*Ack;
};

}}