#ifndef GCOM_PORT_H
#define GCOM_PORT_H

#include <gcom/core/globals.h>
#include <gcom/core/base.h>
#include <gcom/core/link.h>
#include <gcom/core/packet.h>
#include <memory>

namespace gcom
{
	class port : public base
	{
	protected:
		port();

	public:
		link* get_link();
	public:
		void set_link(std::shared_ptr<link> link);

	protected:
		virtual int inter_start() override final;
		virtual void inter_stop() override final;
	};

	class input : public port
	{
	protected:
		input();

	private:
		virtual int on_start() override final;
		virtual void on_stop() override final;

	public:
		int recv(std::shared_ptr<packet> &packet);
		int recv(std::shared_ptr<packet> &packet, double timeout_sec);
	protected:
		virtual int on_recv(std::shared_ptr<packet> &packet);

		friend std::shared_ptr<input> new_input(std::string name = "unnamed input");
	};

	std::shared_ptr<input> new_input(std::string name);

	class output : public port
	{
	protected:
		output();

	private:
		virtual int on_start() override final;
		virtual void on_stop() override final;

	public:
		int send(std::shared_ptr<packet> &packet);
		int send(std::shared_ptr<packet> &packet, double timeout_sec);
	protected:
		virtual int on_send(std::shared_ptr<packet> &packet);

		friend std::shared_ptr<output> new_output(std::string name = "unnamed output");
	};

	std::shared_ptr<output> new_output(std::string name);
}

#endif
