#ifndef GCOM_BASE_H
#define GCOM_BASE_H

#include <gcom/core/defs.h>
#include <gcom/core/meta.h>
#include <gcom/utils/shared_var.h>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

namespace gcom
{
	/// \brief Base class for all classes that have a **name**, a **state**, can hold children objects, and can be started and stopped.
	/// All classes inheriting gcom::base has the method start(), which first starts all the children, and then starts itself.
	///
	/// Library users should not inherit from this class. Instead, they should inherit gcom::link, gcom::computer, or gcom::graph.
	/// Library developers may inherit this class to create other gcom classes, whose objects could be held by other gcom::base derived objects.
	///
	/// **parent** attribute is handled by add_child() and remove_children() methods automaticly.
	class base : public meta
	{
	protected:
		/// \brief Default constructor
		base();

	public:
		/// \brief Starts the object, including all the children.
		///
		/// When start() is called;
		/// 1. start() method of the children objects are called one by one. If all returns **GCOM_OK**, execution continues. If any returns some value other than **GCOM_OK**, stop() method is called and the first encountered error is returned.
		/// 2. inter_start() method is called. inter_start() method may be overriden by the library developers, not by users. This method is intended for internal initializations. If inter_start() returns **GCOM_OK**, execution continue. Else, stop() method is called and the encountered error is returned.
		/// 3. on_start() method is called. on_start() method may be overriden by the library users, not by developers. If on_start() returns **GCOM_OK**, execution continue. Else, stop() method is called and the encountered error is returned.
		/// 4. **state** attribute is set accordingly.
		int start();

		/// \brief Stops the object, including all the children.
		/// \details When stop() is called, almost the reverse operation is done.
		/// Only similarity is, inter_stop() is called before on_stop().
		void stop();

	protected:
		/// \brief See start().
		virtual int inter_start();

		/// \brief See stop().
		virtual void inter_stop();

	private:
		/// \brief See start().
		virtual int on_start();

		/// \brief See stop().
		virtual void on_stop();

	private:
		/// \brief Holds the given name of the object. **name** need not be unique.
		std::string m_name;

	public:
		/// \brief Returns the name of the object.
		std::string get_name();

		/// \brief Sets the name of the object.
		void set_name(std::string&);

	private:
		/// \brief Holds the current state of the object.
		/// \details See defs.h for available states.
		shared_var<int> m_state;

	public:
		/// \brief Returns the current state of the object.
		/// \details See defs.h for available states.
		int get_state();

		/// \brief Waits until the state of the object is s.
		/// \details See defs.h for available states.
		void wait_state(int s);

	protected:
		/// \brief Sets the state of the object.
		/// \details See defs.h for available states.
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
