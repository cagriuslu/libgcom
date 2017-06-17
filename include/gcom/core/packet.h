#ifndef GCOM_PACKET_H
#define GCOM_PACKET_H

#include <gcom/core/meta.h>
#include <gcom/core/globals.h>
#include <memory>

namespace gcom
{
	class packet : public meta
	{
	protected:
		packet()
		{
			set_id(g_packet_id++);
			set_type(GCOM_PACKET);
		}

		template <class T> friend std::shared_ptr<packet> new_packet()
		{
			return std::shared_ptr<packet>(new T);
		}
	};

	template <class T> std::shared_ptr<packet> new_packet();
}

#endif
