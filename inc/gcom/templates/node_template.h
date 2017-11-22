#ifndef GCOM_NODE_TEMPLATE_H
#define GCOM_NODE_TEMPLATE_H

template <class T> std::shared_ptr<gcom::node> gcom::new_node(std::string name)
{
	auto n = new T;
	n->set_name(name);
	return std::shared_ptr<gcom::node>(n);
}

template <class T> int gcom::new_connection(gcom::output *out, gcom::input *in)
{
	if (!in || !out)
		return GCOMERR_ARGNULL;
	auto l = gcom::new_link<T>();
	in->set_link(l);
	out->set_link(l);
	return GCOM_OK;
}

#endif
