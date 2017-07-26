#ifndef GCOM_SHARED_VAR_H
#define GCOM_SHARED_VAR_H

#include <mutex>
#include <condition_variable>

namespace gcom
{
	template <class T> class shared_var
	{
	private:
		T _t;
		std::mutex _mutex;
		std::condition_variable _cond;
	public:
		void set(T t);
		T get();
		void wait(T t);
	};
}

#include <gcom/templates/shared_var_template.h>

#endif
