#include <gcom/core/port.h>

gcom::port::port()
{
	set_id(gcom::g_port_id++);
	set_type(GCOMCL_PORT);
}

gcom::link* gcom::port::get_link()
{
	return static_cast<gcom::link*>(get_child(0));
}

void gcom::port::set_link(std::shared_ptr<gcom::link> link)
{
	remove_children();
	add_child(link);
}

int gcom::port::inter_start() { return GCOM_OK; }

void gcom::port::inter_stop() {}

gcom::input::input()
{
	set_type(GCOMCL_INPUT);
}

int gcom::input::on_start() { return GCOM_OK; }

void gcom::input::on_stop() {}

int gcom::input::recv(std::shared_ptr<gcom::packet> &packet)
{
	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	auto link = get_link();
	if (link)
	{
		int result = link->get(packet);
		if (result == GCOM_OK)
			return on_recv(packet);
		else
			return result;
	}
	else
	{
		return GCOMERR_NOTCONN;
	}
}

int gcom::input::recv(std::shared_ptr<gcom::packet> &packet, double timeout_sec)
{
	if (timeout_sec < 0.0)
		return GCOMERR_ARGNEG;
	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	auto link = get_link();
	if (link)
	{
		int result = link->get(packet, timeout_sec);
		if (result == GCOM_OK)
			return on_recv(packet);
		else
			return result;
	}
	else
	{
		return GCOMERR_NOTCONN;
	}
}

int gcom::input::on_recv(std::shared_ptr<gcom::packet> &packet)
{
	(void) packet;
	return GCOM_OK;
}

gcom::output::output()
{
	set_type(GCOMCL_OUTPUT);
}

int gcom::output::on_start() { return GCOM_OK; }

void gcom::output::on_stop() {}

int gcom::output::send(std::shared_ptr<gcom::packet> &packet)
{
	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	int result = on_send(packet);
	if (result != GCOM_OK)
		return result;

	auto link = get_link();
	if (link)
		return link->put(packet);
	else
		return GCOMERR_NOTCONN;
}

int gcom::output::send(std::shared_ptr<gcom::packet> &packet, double timeout_sec)
{
	if (timeout_sec < 0.0)
		return GCOMERR_ARGNEG;
	if (get_state() != GCOMST_STARTED)
		return GCOMERR_STOPPED;

	int result = on_send(packet);
	if (result != GCOM_OK)
		return result;

	auto link = get_link();
	if (link)
		return link->put(packet, timeout_sec);
	else
		return GCOMERR_NOTCONN;
}

int gcom::output::on_send(std::shared_ptr<gcom::packet> &packet)
{
	(void) packet;
	return GCOM_OK;
}

std::shared_ptr<gcom::input> gcom::new_input(std::string name)
{
	auto p = new gcom::input;
	p->set_name(name);
	return std::shared_ptr<gcom::input>(p);
}

std::shared_ptr<gcom::output> gcom::new_output(std::string name)
{
	auto p = new gcom::output;
	p->set_name(name);
	return std::shared_ptr<gcom::output>(p);
}
