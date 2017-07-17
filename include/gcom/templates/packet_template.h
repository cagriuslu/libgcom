#ifndef GCOM_PACKET_TEMPLATE_H
#define GCOM_PACKET_TEMPLATE_H

template <class T> std::shared_ptr<gcom::packet> gcom::new_packet()
{
	return std::shared_ptr<gcom::packet>(new T);
}

#endif
