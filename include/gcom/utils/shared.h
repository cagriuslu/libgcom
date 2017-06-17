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
		void set(T t)
		{
			std::unique_lock<std::mutex> lock(_mutex);
			_t = t;
			_cond.notify_all();
		}

		T get()
		{
			std::unique_lock<std::mutex> lock(_mutex);
			return _t;
		}

		void wait(T t)
		{
			std::unique_lock<std::mutex> lock(_mutex);
			while (_t != t)
				_cond.wait(lock);
		}
	};
}

#endif
