#include <gcom/core/link.h>

gcom::link::link()
{
	set_id(g_link_id++);
	set_type(GCOMCL_LINK);
}

int gcom::link::inter_start()
{
	set_abort(false);
	return GCOM_OK;
}

void gcom::link::inter_stop()
{
	set_abort(true);
	m_cond_get.notify_all();
	m_cond_put.notify_all();
}

bool gcom::link::get_abort()
{
	return m_abort.get();
}

void gcom::link::set_abort(bool a)
{
	m_abort.set(a);
}

int gcom::link::get(std::shared_ptr<packet> &pkt)
{
	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (empty())
		{
			m_cond_put.wait(lock);
			if (get_abort())
				return GCOMERR_STOPPED;
		}
		int result = get_impl(pkt);
		if (result == GCOM_OK)
			m_cond_get.notify_one();
		return result;
	}
}

int gcom::link::get(std::shared_ptr<packet> &pkt, double timeout_sec)
{
	if (timeout_sec < 0.0)
		return GCOMERR_ARGNEG;

	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (empty())
		{
			if (m_cond_put.wait_for(lock, std::chrono::duration<double>(timeout_sec)) == std::cv_status::timeout)
				return GCOMERR_TIMEOUT;
			if (get_abort())
				return GCOMERR_STOPPED;
		}
		int result = get_impl(pkt);
		if (result == GCOM_OK)
			m_cond_get.notify_one();
		return result;
	}
}

int gcom::link::put(std::shared_ptr<packet> &pkt)
{
	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (full())
		{
			m_cond_get.wait(lock);
			if (get_abort())
				return GCOMERR_STOPPED;
		}
		int result = put_impl(pkt);
		if (result == GCOM_OK)
			m_cond_put.notify_one();
		return result;
	}
}

int gcom::link::put(std::shared_ptr<packet> &pkt, double timeout_sec)
{
	if (timeout_sec < 0.0)
		return GCOMERR_ARGNEG;

	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (full())
		{
			if (m_cond_get.wait_for(lock, std::chrono::duration<double>(timeout_sec)) == std::cv_status::timeout)
				return GCOMERR_TIMEOUT;
			if (get_abort())
				return GCOMERR_STOPPED;
		}
		int result = put_impl(pkt);
		if (result == GCOM_OK)
			m_cond_put.notify_one();
		return result;
	}
}
