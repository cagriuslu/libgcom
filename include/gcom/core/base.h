#ifndef GCOM_BASE_H
#define GCOM_BASE_H

#include <gcom/core/defs.h>
#include <gcom/core/meta.h>
#include <gcom/utils/shared.h>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

namespace gcom
{
	/// \brief Base class for all classes that have a **name**, a **state**, and can hold children objects. All classes inheriting gcom::base has the method start(), which first starts all the children, and then starts itself.
	///
	/// Library users should not inherit from this class. Instead, they should inherit gcom::link, gcom::computer, or gcom::graph.
	/// Library developers may inherit this class to create other classes, whose objects could be held by other gcom::base derived objects.
	///
	/// When start() is called;
	/// 1. start() method of the children objects are called one by one. If all returns **GCOM_OK**, execution continues. If any returns some value other than **GCOM_OK**, stop() method is called and the first encountered error is returned.
	/// 2. inter_start() method is called. inter_start() method may be overriden by the library developers, not by users. This method is intended for internal initializations. If inter_start() returns **GCOM_OK**, execution continue. Else, stop() method is called and the encountered error is returned.
	/// 3. on_start() method is called. on_start() method may be overriden by the library users, not by developers. If on_start() returns **GCOM_OK**, execution continue. Else, stop() method is called and the encountered error is returned.
	/// 4. **state** attribute is set accordingly.
	///
	/// When stop() is called, almost the reverse operation is done. Only difference is, inter_stop() is called before on_stop().
	///
	/// **name** need not be unique. **parent** attribute is handled by add_child() and remove_children() methods automaticly.
	class base : public meta
	{
	protected:
		base();

	public:
		int start();
		void stop();
	protected:
		virtual int inter_start();
		virtual void inter_stop();
	private:
		virtual int on_start();
		virtual void on_stop();

	private:
		std::string m_name;
	public:
		std::string get_name();
		void set_name(std::string&);

	private:
		shared<int> m_state;
	public:
		int get_state();
		void wait_state(int);
	protected:
		void set_state(int);

	private:
		std::vector< std::shared_ptr<base> > m_children;
	public:
		base* get_child(size_t);
		size_t get_children_count();
		void add_child(std::shared_ptr<base>);
		void remove_children();

	private:
		base *m_parent;
	public:
		base* get_parent();
	private:
		void set_parent(base*);
	};
}

#endif
