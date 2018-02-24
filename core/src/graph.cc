#include <gcom/core/graph.h>

gcom::graph::graph()
{
	set_type(GCOMCL_GRAPH);
}

int gcom::graph::inter_start()
{
	return GCOM_OK;
}

void gcom::graph::inter_stop() { }

int gcom::graph::on_start()
{
	return GCOM_OK;
}

void gcom::graph::on_stop() { }

gcom::input* gcom::graph::get_input(size_t no)
{
	return no < m_input_matchings.size() ? m_input_matchings[no] : nullptr;
}

gcom::output* gcom::graph::get_output(size_t no)
{
	return no < m_output_matchings.size() ? m_output_matchings[no] : nullptr;
}

int gcom::graph::add_input(input *p)
{
	if (p)
	{
		m_input_matchings.push_back(p);
		return GCOM_OK;
	}
	else
		return GCOMERR_UNKNOWN;
}

int gcom::graph::add_output(output *p)
{
	if (p)
	{
		m_output_matchings.push_back(p);
		return GCOM_OK;
	}
	else
		return GCOMERR_UNKNOWN;
}
