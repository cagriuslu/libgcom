#include <gcom/core/node.h>

gcom::node::node()
{
	set_id(gcom::g_node_id++);
	set_type(GCOMCL_NODE);
}
