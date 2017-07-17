#ifndef GCOM_RING_BUFFER_LINK_H
#define GCOM_RING_BUFFER_LINK_H

#include <gcom/core/link.h>
#include <gcom/utils/ring_buffer.h>

namespace gcom
{
	class ring_buffer_link : public link
	{
	public:
		ring_buffer_link();

	protected:
		virtual int on_start() override final;
		virtual void on_stop() override final;

	private:
		ring_buffer< std::shared_ptr<packet> > *m_buffer;
		virtual int get_impl(std::shared_ptr<packet> &pkt) override final;
		virtual int put_impl(std::shared_ptr<packet> &pkt) override final;
	public:
		virtual bool empty() override final;
		virtual bool full() override final;
	};
}

#endif
