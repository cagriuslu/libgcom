#ifndef GCOM_COMPUTER_H
#define GCOM_COMPUTER_H

#include <gcom/core/node.h>
#include <gcom/utils/shared_var.h>
#include <gcom/core/port.h>
#include <vector>
#include <thread>

namespace gcom
{
	class computer : public node
	{
	public:
		computer();

		// Starting/Stopping
	protected:
		virtual int inter_start() override final;
		virtual void inter_stop() override final;
		virtual int on_loop() = 0;
	private:
		virtual int on_start() override;
		virtual void on_stop() override;

		// Thread management
	private:
		std::thread *m_thread;
		int m_thread_result;
		shared_var<bool> m_abort_thread;
		static void thread_func(computer *computer);

		// Members and their getters/setters
	private:
		std::vector<input*> m_inputs;
		std::vector<output*> m_outputs;
	public:
		virtual input* get_input(size_t) override final;
		virtual output* get_output(size_t) override final;
	protected:
		void add_input(std::string = "unnamed input");
		void add_output(std::string = "unnamed output");
	};
}

#endif
