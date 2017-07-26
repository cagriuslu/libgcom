#ifndef GCOM_SHARED_VAR_TEMPLATE_H
#define GCOM_SHARED_VAR_TEMPLATE_H

template <class T> void gcom::shared_var<T>::set(T t)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_t = t;
	_cond.notify_all();
}

template <class T> T gcom::shared_var<T>::get()
{
	std::unique_lock<std::mutex> lock(_mutex);
	return _t;
}

template <class T> void gcom::shared_var<T>::wait(T t)
{
	std::unique_lock<std::mutex> lock(_mutex);
	while (_t != t)
		_cond.wait(lock);
}

#endif
