#ifndef GCOM_LINK_H
#define GCOM_LINK_H

#include <gcom/core/base.h>
#include <gcom/core/globals.h>
#include <gcom/core/packet.h>
#include <gcom/utils/shared_var.h>
#include <chrono>
#include <mutex>
#include <condition_variable>

namespace gcom
{
	class link : public base
	{
	protected:
		link();

	public:
		virtual int inter_start() override final;
		virtual void inter_stop() override final;

	private:
		shared_var<bool> m_abort;
	protected:
		bool get_abort();
	protected:
		void set_abort(bool a);

	private:
		std::mutex m_mutex;
		std::condition_variable m_cond_get;
		std::condition_variable m_cond_put;
	public:
		int get(std::shared_ptr<packet>&);
		int get(std::shared_ptr<packet> &pkt, double timeout_sec);
		int put(std::shared_ptr<packet>&);
		int put(std::shared_ptr<packet> &pkt, double timeout_sec);
	protected:
		virtual bool empty() = 0;
		virtual bool full() = 0;
		virtual int get_impl(std::shared_ptr<packet> &pkt) = 0;
		virtual int put_impl(std::shared_ptr<packet> &pkt) = 0;

		template <class T> friend std::shared_ptr<link> new_link(std::string name = "unnamed link");
	};

	template <class T> std::shared_ptr<link> new_link(std::string name);
}

#include <gcom/templates/link_template.h>

#endif
