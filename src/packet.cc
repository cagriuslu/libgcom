#include <gcom/core/packet.h>

gcom::packet::packet()
{
	set_id(gcom::g_packet_id++);
	set_type(GCOM_PACKET);
}

std::shared_ptr<gcom::packet> gcom::packet::soft_copy()
{
	return std::shared_ptr<gcom::packet>(this);
}
