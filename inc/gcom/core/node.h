#ifndef GCOM_NODE_H
#define GCOM_NODE_H

#include <gcom/core/base.h>
#include <gcom/core/globals.h>
#include <gcom/core/port.h>

namespace gcom
{
	class node;

	template <class T> std::shared_ptr<node> new_node(std::string name = "unnamed node");

	class node : public base
	{
	protected:
		node();

	public:
		virtual input* get_input(size_t) = 0;
		virtual output* get_output(size_t) = 0;

		template <class T> friend std::shared_ptr<node> new_node(std::string name);
	};

	template <class T> int new_connection(output *out, input *in);
}

#include <gcom/templates/node_template.h>

#endif
