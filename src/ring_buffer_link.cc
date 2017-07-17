#include <gcom/links/ring_buffer_link.h>

int gcom::ring_buffer_link::on_start()
{
	m_buffer = new gcom::ring_buffer< std::shared_ptr<gcom::packet> >(256);
	return GCOM_OK;
}

void gcom::ring_buffer_link::on_stop()
{
	delete m_buffer;
	m_buffer = nullptr;
}

int gcom::ring_buffer_link::get_impl(std::shared_ptr<packet> &pkt)
{
	if (m_buffer)
		return m_buffer->try_get(pkt) ? GCOM_OK : GCOMERR_UNKNOWN;
	else
		return GCOMERR_UNKNOWN;
}

int gcom::ring_buffer_link::put_impl(std::shared_ptr<packet> &pkt)
{
	if (m_buffer)
		return m_buffer->try_put(pkt) ? GCOM_OK : GCOMERR_UNKNOWN;
	else
		return GCOMERR_UNKNOWN;
}

bool gcom::ring_buffer_link::empty()
{
	if (m_buffer)
		return m_buffer->empty();
	else
		return true;
}

bool gcom::ring_buffer_link::full()
{
	if (m_buffer)
		return m_buffer->full();
	else
		return true;
}
