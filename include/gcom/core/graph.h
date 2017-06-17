#ifndef GCOM_GRAPH_H
#define GCOM_GRAPH_H

#include <gcom/core/node.h>
#include <gcom/core/port.h>
#include <memory>
#include <vector>

namespace gcom
{
	class graph : public node
	{
	protected:
		virtual int inter_start() override final { return GCOM_OK; }
		virtual void inter_stop() override final {}
	private:
		virtual int on_start() override { return GCOM_OK; }
		virtual void on_stop() override {}

	private:
		std::vector<input*> m_input_matchings;
		std::vector<output*> m_output_matchings;
	public:
		virtual input* get_input(size_t no) override final;
		virtual output* get_output(size_t no) override final;
	protected:
		int add_input(input*);
		int add_output(output*);
	};
}

#endif
