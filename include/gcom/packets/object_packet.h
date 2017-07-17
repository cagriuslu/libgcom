#ifndef GCOM_OBJECT_PACKET_H
#define GCOM_OBJECT_PACKET_H

#include <gcom/core/packet.h>

namespace gcom
{
	template <class T> class object_packet : public packet
	{
	private:
		T m_obj;

	public:
		void set(T& new_value);
		T& get();

		virtual std::shared_ptr<packet> hard_copy() override final;
	};
}

#include <gcom/templates/object_packet_template.h>

#endif
