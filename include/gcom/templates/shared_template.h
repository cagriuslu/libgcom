#ifndef GCOM_SHARED_TEMPLATE_H
#define GCOM_SHARED_TEMPLATE_H

template <class T> void gcom::shared<T>::set(T t)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_t = t;
	_cond.notify_all();
}

template <class T> T gcom::shared<T>::get()
{
	std::unique_lock<std::mutex> lock(_mutex);
	return _t;
}

template <class T> void gcom::shared<T>::wait(T t)
{
	std::unique_lock<std::mutex> lock(_mutex);
	while (_t != t)
		_cond.wait(lock);
}

#endif
