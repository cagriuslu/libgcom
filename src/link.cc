#include <gcom/core/link.h>

int gcom::link::get(std::shared_ptr<packet> &pkt)
{
	if (get_state() != GCOM_STARTED)
		return GCOM_NOT_STARTED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (empty())
			m_cond_put.wait(lock);
		int result = get_impl(pkt);
		if (result == GCOM_OK)
			m_cond_get.notify_one();
		return result;
	}
}

int gcom::link::get(std::shared_ptr<packet> &pkt, double timeout_sec)
{
	if (timeout_sec < 0.0)
		return GCOM_ERR;

	if (get_state() != GCOM_STARTED)
		return GCOM_NOT_STARTED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (empty())
		{
			if (m_cond_put.wait_for(lock, std::chrono::duration<double>(timeout_sec)) == std::cv_status::timeout)
				return GCOM_TIMEDOUT;
		}
		int result = get_impl(pkt);
		if (result == GCOM_OK)
			m_cond_get.notify_one();
		return result;
	}
}

int gcom::link::put(std::shared_ptr<packet> &pkt)
{
	if (get_state() != GCOM_STARTED)
		return GCOM_NOT_STARTED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (full())
			m_cond_get.wait(lock);
		int result = put_impl(pkt);
		if (result == GCOM_OK)
			m_cond_put.notify_one();
		return result;
	}
}

int gcom::link::put(std::shared_ptr<packet> &pkt, double timeout_sec)
{
	if (timeout_sec < 0.0)
		return GCOM_ERR;

	if (get_state() != GCOM_STARTED)
		return GCOM_NOT_STARTED;

	if (1)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (full())
		{
			if (m_cond_get.wait_for(lock, std::chrono::duration<double>(timeout_sec)) == std::cv_status::timeout)
				return GCOM_TIMEDOUT;
		}
		int result = put_impl(pkt);
		if (result == GCOM_OK)
			m_cond_put.notify_one();
		return result;
	}
}
