#include <gcom/core/graph.h>

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
		return GCOM_ERR;
}

int gcom::graph::add_output(output *p)
{
	if (p)
	{
		m_output_matchings.push_back(p);
		return GCOM_OK;
	}
	else
		return GCOM_ERR;
}
