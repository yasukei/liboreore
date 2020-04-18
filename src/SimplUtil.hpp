#pragma once

template <typename T>
class EventListener
{
	virtual void notifyEvent(T event) = 0;
};

#include <vector>
template <typename T>
class EventListeners
{
public:
	void addListener(EventListener<T>& listener)
	{
		_listeners.push_back(listener);
	}
	void notifyEvent(T event)
	{
		for (EventListener<T>& listener in _listeners)
		{
			listener.notifyEvent(event);
		}
	}
private:
	std::vector<EventListener<T>&> _listeners;
};

#include <string.h>
class SimpleDictionary
{
public:
	~SimpleDictionary()
	{
		// free resource
	}

	void setValue(const char* page, const char* section, const char* entry, const char* value)
	{
		;
	}
	void setValue(const char* section, const char* entry, const char* value)
	{
		setValue("", entry, value);
	}
	void setValue(const char* entry, const char* value)
	{
		setValue("", "", value);
	}
	bool getValue(const char* page, const char* section, const char* entry, const char** value)
	{
		;
	}
	bool getValue(const char* section, const char* entry, const char** value)
	{
		return getValue("", section, entry, value);
	}
	bool getValue(const char* entry, const char** value)
	{
		return getValue("", "", entry, value);
	}

	bool setValuesFromIniFile()
	{
		return false;
	}
private:
};
