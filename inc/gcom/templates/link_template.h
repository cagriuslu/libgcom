#ifndef GCOM_LINK_TEMPLATE_H
#define GCOM_LINK_TEMPLATE_H

template <class T> std::shared_ptr<gcom::link> gcom::new_link(std::string name)
{
	auto l = new T;
	l->set_name(name);
	return std::shared_ptr<gcom::link>(l);
}

#endif
