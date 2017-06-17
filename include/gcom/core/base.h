#ifndef GCOM_BASE_H
#define GCOM_BASE_H

#include <gcom/core/meta.h>
#include <gcom/core/globals.h>
#include <gcom/utils/shared.h>
#include <vector>

namespace gcom
{
	class base : public meta
	{
	protected:
		base()
		{
			set_id(g_base_id++);
			set_type(GCOM_BASE);
			set_state(GCOM_STOPPED);
			set_parent(nullptr);
		}

	private:
		std::string m_name;
	public:
		std::string get_name() { return m_name; }
	public:
		void set_name(std::string &name) { m_name = name; }

	private:
		shared<int> m_state;
	public:
		int get_state() { return m_state.get(); }
	public:
		void wait_state(int state) { m_state.wait(state); }
	protected:
		void set_state(int state) { m_state.set(state); }

	private:
		std::vector< std::shared_ptr<base> > m_children;
	public:
		base* get_child(size_t no) { return no < m_children.size() ? m_children[no].get() : nullptr; }
		size_t get_children_count() { return m_children.size(); }
	public:
		void add_child(std::shared_ptr<base> obj) { if (obj) { obj->set_parent(this); m_children.push_back(obj); } }
		void remove_children() { m_children.clear(); }

	private:
		base *m_parent;
	public:
		base* get_parent() { return m_parent; }
	private:
		void set_parent(base *parent) { m_parent = parent; }

	public:
		int start()
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
			if ((result = inter_start()) != GCOM_OK)
				return result;
			if ((result = on_start()) != GCOM_OK)
			{
				inter_stop();
				return result;
			}
			set_state(GCOM_STARTED);
			return GCOM_OK;
		}
		void stop()
		{
			if (get_state() == GCOM_STOPPED)
				return;

			set_state(GCOM_STOPPED);
			on_stop();
			inter_stop();
			for (size_t i = 0; i < get_children_count(); i++)
				get_child(i)->stop();
		}
	protected:
		virtual int inter_start() = 0;
		virtual void inter_stop() = 0;
	private:
		virtual int on_start() = 0;
		virtual void on_stop() = 0;
	};
}

#endif
