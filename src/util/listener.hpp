#pragma once

#include <vector>

namespace util
{

template <typename T>
class Listener
{
public:
	virtual void notify(T event) = 0;
};

template <typename T>
class Listeners
{
public:
	void addListener(Listener<T>& listener)
	{
		_listeners.push_back(&listener);
	}
	void notify(T event)
	{
		for (Listener<T>* listener : _listeners)
		{
			listener->notify(event);
		}
	}
private:
	std::vector<Listener<T>*> _listeners;
};
}
