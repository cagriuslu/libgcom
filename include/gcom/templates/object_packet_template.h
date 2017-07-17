#ifndef GCOM_OBJECT_PACKET_TEMPLATE_H
#define GCOM_OBJECT_PACKET_TEMPLATE_H

template <class T> void gcom::object_packet<T>::set(T& new_value)
{
	m_obj = new_value;
}

template <class T> T& gcom::object_packet<T>::get()
{
	return m_obj;
}

template <class T> std::shared_ptr<gcom::packet> gcom::object_packet<T>::hard_copy()
{
	auto p = new object_packet<T>();
	p->set(get());
	return std::shared_ptr<gcom::packet>(p);
}

#endif
