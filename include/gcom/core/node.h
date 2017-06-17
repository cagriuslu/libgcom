#ifndef GCOM_NODE_H
#define GCOM_NODE_H

#include <gcom/core/base.h>
#include <gcom/core/globals.h>
#include <gcom/core/port.h>

namespace gcom
{
	class node : public base
	{
	protected:
		node()
		{
			set_id(g_node_id++);
			set_type(GCOM_NODE);
		}

	public:
		virtual input* get_input(size_t) = 0;
		virtual output* get_output(size_t) = 0;

		template <class T> friend std::shared_ptr<node> new_node(std::string name = "unnamed node")
		{
			auto n = new T;
			n->set_name(name);
			return std::shared_ptr<node>(n);
		}
	};

	template <class T> std::shared_ptr<node> new_node(std::string name);

	template <class T> int new_connection(output *out, input *in)
	{
		if (!in || !out)
			return GCOM_ERR;
		auto l = new_link<T>();
		in->set_link(l);
		out->set_link(l);
		return GCOM_OK;
	}
}

#endif
