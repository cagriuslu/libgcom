#ifndef GCOM_SHARED_H
#define GCOM_SHARED_H

#include <mutex>
#include <condition_variable>

namespace gcom
{
	template <class T> class shared
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

#include <gcom/templates/shared_template.h>

#endif
