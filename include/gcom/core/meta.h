#ifndef GCOM_META_H
#define GCOM_META_H

#include <gcom/core/defs.h>
#include <cstdlib>

namespace gcom
{
	class meta
	{
	private:
		size_t m_id;
	public:
		size_t get_id() { return m_id; }
	protected:
		void set_id(size_t id) { m_id = id; }

	private:
		int m_type;
	public:
		int get_type() { return m_type; }
	protected:
		void set_type(int type) { m_type = type; }
	};
}

#endif
