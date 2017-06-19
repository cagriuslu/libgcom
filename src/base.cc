#include <gcom/core/base.h>
#include <gcom/core/globals.h>

gcom::base::base()
{
	set_id(gcom::g_base_id++);
	set_type(GCOM_BASE);
	set_state(GCOM_STOPPED);
	set_parent(nullptr);
}

int gcom::base::start()
{
	if (get_state() == GCOM_STARTED)
		return GCOM_OK;

	int result;
	for (size_t i = 0; i < get_children_count(); i++)
	{
		result = get_child(i)->start();
		if (result != GCOM_OK)
		{
			stop();
			return result;
		}
	}
	if ((result = on_start()) != GCOM_OK)
		return result;
	if ((result = inter_start()) != GCOM_OK)
	{
		on_stop();
		return result;
	}
	set_state(GCOM_STARTED);
	return GCOM_OK;
}

void gcom::base::stop()
{
	if (get_state() == GCOM_STOPPED)
		return;

	set_state(GCOM_STOPPED);
	inter_stop();
	on_stop();
	for (size_t i = 0; i < get_children_count(); i++)
		get_child(i)->stop();
}

int gcom::base::inter_start() { return GCOM_OK; }

void gcom::base::inter_stop() {}

int gcom::base::on_start() { return GCOM_OK; }

void gcom::base::on_stop() {}

std::string gcom::base::get_name() { return m_name; }

int gcom::base::get_state() { return m_state.get(); }

void gcom::base::wait_state(int state) { m_state.wait(state); }

gcom::base* gcom::base::get_child(size_t no) { return no < m_children.size() ? m_children[no].get() : nullptr; }

size_t gcom::base::get_children_count() { return m_children.size(); }

gcom::base* gcom::base::get_parent() { return m_parent; }

void gcom::base::set_name(std::string &name) { m_name = name; }

void gcom::base::add_child(std::shared_ptr<base> obj) { if (obj) { obj->set_parent(this); m_children.push_back(obj); } }

void gcom::base::remove_children()
{
	for (size_t i = 0; i < get_children_count(); i++)
		get_child(i)->set_parent(nullptr);
	m_children.clear();
}

void gcom::base::set_state(int state) { m_state.set(state); }

void gcom::base::set_parent(gcom::base *parent) { m_parent = parent; }
