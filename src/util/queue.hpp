#pragma once

#include <deque>

namespace util
{

template <typename T>
class Queue
{
public:
	void enqueue(T elem)
	{
		_queue.push_back(elem);
	}
	bool dequue(T* elem)
	{
		if (_queue.empty())
		{
			return false;
		}

		*elem = _queue.front();
		_queue.pop_front();
		return true;
	}
private:
	std::deque<T> _queue;
};

}
