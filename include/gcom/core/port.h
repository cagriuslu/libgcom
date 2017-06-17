#ifndef GCOM_PORT_H
#define GCOM_PORT_H

#include <gcom/core/base.h>
#include <gcom/core/link.h>
#include <gcom/core/packet.h>
#include <memory>

namespace gcom
{
	class port : public base
	{
	protected:
		port()
		{
			set_id(g_port_id++);
			set_type(GCOM_PORT);
		}

	public:
		link* get_link()
		{
			return static_cast<link*>(get_child(0));
		}
	public:
		void set_link(std::shared_ptr<link> link)
		{
			remove_children();
			add_child(link);
		}

	protected:
		virtual int inter_start() override final { return GCOM_OK; }
		virtual void inter_stop() override final {}
	};

	class input : public port
	{
	protected:
		input()
		{
			set_type(GCOM_INPUT);
		}

	private:
		virtual int on_start() override final { return GCOM_OK; }
		virtual void on_stop() override final {}

	public:
		int recv(std::shared_ptr<packet> &packet)
		{
			if (get_state() != GCOM_STARTED)
				return GCOM_NOT_STARTED;

			auto link = get_link();
			if (link)
				return link->get(packet);
			else
				return GCOM_ERR;
		}
		int recv(std::shared_ptr<packet> &packet, double timeout_sec)
		{
			if (timeout_sec < 0.0)
				return GCOM_ERR;
			if (get_state() != GCOM_STARTED)
				return GCOM_NOT_STARTED;

			auto link = get_link();
			if (link)
				return link->get(packet, timeout_sec);
			else
				return GCOM_ERR;
		}

		friend std::shared_ptr<input> new_input(std::string name = "unnamed input")
		{
			auto p = new input;
			p->set_name(name);
			return std::shared_ptr<input>(p);
		}
	};

	class output : public port
	{
	protected:
		output()
		{
			set_type(GCOM_OUTPUT);
		}

	private:
		virtual int on_start() override final { return GCOM_OK; }
		virtual void on_stop() override final {}

	public:
		int send(std::shared_ptr<packet> &packet)
		{
			if (get_state() != GCOM_STARTED)
				return GCOM_NOT_STARTED;

			auto link = get_link();
			if (link)
				return link->put(packet);
			else
				return GCOM_ERR;
		}
		int send(std::shared_ptr<packet> &packet, double timeout_sec)
		{
			if (timeout_sec < 0.0)
				return GCOM_ERR;
			if (get_state() != GCOM_STARTED)
				return GCOM_NOT_STARTED;

			auto link = get_link();
			if (link)
				return link->put(packet, timeout_sec);
			else
				return GCOM_ERR;
		}

		friend std::shared_ptr<output> new_output(std::string name = "unnamed output")
		{
			auto p = new output;
			p->set_name(name);
			return std::shared_ptr<output>(p);
		}
	};

	std::shared_ptr<input> new_input(std::string name);
	std::shared_ptr<output> new_output(std::string name);
}

#endif
