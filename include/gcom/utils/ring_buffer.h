#ifndef GCOM_RING_BUFFER_H
#define GCOM_RING_BUFFER_H

#include <cstdlib>
#include <vector>

namespace gcom
{
	template <class T> class ring_buffer
	{
	public:
		ring_buffer(size_t size);

	private:
		std::vector<T> m_buffer;
		size_t m_size;
		size_t m_begin;
		size_t m_end;
		bool m_is_wrapped;

	public:
		bool empty();
		bool full();
		bool try_put(T &obj);
		bool try_get(T &obj);
	};
}

#include <gcom/templates/ring_buffer_template.h>

#endif
