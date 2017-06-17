#ifndef GCOM_RING_BUFFER_H
#define GCOM_RING_BUFFER_H

#include <cstdlib>
#include <vector>

namespace gcom
{
	template <class T> class ring_buffer
	{
	public:
		ring_buffer(size_t size)
		{
			m_buffer.resize(size);
			m_size = size;
			m_begin = 0;
			m_end = 0;
			m_is_wrapped = false;
		}

	private:
		std::vector<T> m_buffer;
		size_t m_size;
		size_t m_begin;
		size_t m_end;
		bool m_is_wrapped;

	public:
		bool empty() { return (m_begin == m_end && m_is_wrapped == false); }
		bool full() { return m_is_wrapped; }
		bool try_put(T &obj)
		{
			if (m_is_wrapped)
				return false;

			m_buffer[m_end] = obj;
			m_end = (m_end + 1) % m_size;

			if (m_end == m_begin)
				m_is_wrapped = true;

			return true;
		}
		bool try_get(T &obj)
		{
			if (empty())
			{
				return false;
			}
			else
			{
				obj = m_buffer[m_begin];
				m_buffer[m_begin] = T();
				m_begin = (m_begin + 1) % m_size;
				m_is_wrapped = false;
				return true;
			}
		}
	};
}

#endif
