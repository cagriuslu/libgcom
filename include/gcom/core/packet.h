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
		packet();

	public:
		std::shared_ptr<packet> soft_copy();
		virtual std::shared_ptr<packet> hard_copy() = 0;

		template <class T> friend std::shared_ptr<packet> new_packet()
		{
			return std::shared_ptr<packet>(new T);
		}
	};

	template <class T> std::shared_ptr<packet> new_packet();
}

#endif
