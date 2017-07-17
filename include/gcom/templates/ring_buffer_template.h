#ifndef GCOM_RING_BUFFER_TEMPLATE_H
#define GCOM_RING_BUFFER_TEMPLATE_H

template <class T> gcom::ring_buffer<T>::ring_buffer(size_t size)
{
	m_buffer.resize(size);
	m_size = size;
	m_begin = 0;
	m_end = 0;
	m_is_wrapped = false;
}

template <class T> bool gcom::ring_buffer<T>::empty()
{
	return (m_begin == m_end && m_is_wrapped == false);
}

template <class T> bool gcom::ring_buffer<T>::full()
{
	return m_is_wrapped;
}

template <class T> bool gcom::ring_buffer<T>::try_put(T &obj)
{
	if (m_is_wrapped)
		return false;

	m_buffer[m_end] = obj;
	m_end = (m_end + 1) % m_size;

	if (m_end == m_begin)
		m_is_wrapped = true;

	return true;
}

template <class T> bool gcom::ring_buffer<T>::try_get(T &obj)
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

#endif
