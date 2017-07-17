#include <gcom/core/computer.h>

gcom::computer::computer()
{
	set_type(GCOMCL_COMPUTER);
}

int gcom::computer::inter_start()
{
	m_thread_result = GCOM_OK;
	m_abort_thread.set(false);
	m_thread = new std::thread(gcom::computer::thread_func, this);
	return GCOM_OK;
}

void gcom::computer::inter_stop()
{
	m_abort_thread.set(true);
	m_thread->join();
	delete m_thread;
	m_thread = nullptr;
}

int gcom::computer::on_start() { return GCOM_OK; }

void gcom::computer::on_stop() {}

gcom::input* gcom::computer::get_input(size_t no)
{
	return no < m_inputs.size() ? m_inputs[no] : nullptr;
}

gcom::output* gcom::computer::get_output(size_t no)
{
	return no < m_outputs.size() ? m_outputs[no] : nullptr;
}

void gcom::computer::add_input(std::string name)
{
	auto port = gcom::new_input(name);
	m_inputs.push_back(port.get());
	add_child(port);
}

void gcom::computer::add_output(std::string name)
{
	auto port = gcom::new_output(name);
	m_outputs.push_back(port.get());
	add_child(port);
}

void gcom::computer::thread_func(computer *worker)
{
	for (;;)
	{
		if (worker->m_abort_thread.get() == true)
		{
			worker->m_thread_result = GCOM_OK;
			return;
		}

		if ((worker->m_thread_result = worker->on_loop()) != GCOM_OK)
		{
			return;
		}
	}
}
