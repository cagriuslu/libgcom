#include <gcom/core/meta.h>

size_t gcom::meta::get_id()
{
	return m_id;
}

void gcom::meta::set_id(size_t id)
{
	m_id = id;
}

int gcom::meta::get_type()
{
	return m_type;
}

void gcom::meta::set_type(int type)
{
	m_type = type;
}
