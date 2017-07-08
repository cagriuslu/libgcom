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
		void set(T& new_value) { m_obj = new_value; }
		T& get() { return m_obj; }

		virtual std::shared_ptr<packet> hard_copy() override final
		{
			auto p = new object_packet<T>();
			p->set(get());
			return std::shared_ptr<packet>(p);
		}
	};
}

#endif
