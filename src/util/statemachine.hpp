#pragma once

#include <map>

#include "SimplUtil.hpp"

template <typename T>
class State
{
public:
	virtual void entry(T) {}
	virtual void exit(T) {}
};

template <typename T>
class Action
{
public:
	virtual void operator()(T context) {}
};

template <typename T>
class Branch
{
public:
	virtual State<T>& operator()(T context) = 0;
};

template <typename T>
class NoBranch : public Branch<T>
{
public:
	NoBranch(State<T>& dst) :
		_dst(dst)
	{
	}
	State<T>& operator()(T context)
	{
		return _dst;
	}
private:
	State<T>& _dst;
};

template <typename T>
class Transition
{
public:
	Transition(State<T>& src, Action<T>& action, Branch<T>& branch) :
		_src(src),
		_action(action),
		_branch(branch)
	{
	}

	State<T>& transit(T context)
	{
		_src.exit(context);
		_action(context);
		
		State<T>& dst = _branch(context);
		_dst.entry(context);

		return _dst;
	}
private:
	State<T>& _src;
	Action<T>& _action;
	Branch<T>& _branch;
};

template <typename T>
class StateMachine
{
public:
	StateMachine(State<T>& initialState) :
		_initialState(initialState),
		_currentState(initialState)
	{
	}
	~StateMachine()
	{
		// TODO: delete transitions

		//NoBranch<T>* noBranch;
		//while (_noBranches.dequue(&noBranch))
		//{
		//	delete noBranch;
		//}
	}
	bool addTransition(State<T>& src, int event, Action<T>& action, Branch<T>& branch)
	{
		Transition<T>* transition = findTransition(&src, event);
		if (transition != nullptr)
		{
			// transition already exists
			return false;
		}

		transition = new Transition<T>(src, action, branch);
		if (transition == nullptr)
		{
			return false;
		}

		std::pair<State<T>*, int> key = std::make_pair(&src, event);
		_transitionMap.insert(std::make_pair(key, transition));
		return true;
	}
	bool addTransition(State<T>& src, int event, Branch<T>& branch)
	{
		static Action<T> doNothing;

		return addTransition(src, dst, event, doNothing);
	}
	bool addTransition(State<T>& src, int event, Action<T>& action, State<T>& dst)
	{
		NoBranch<T>* noBranch = new NoBranch<T>(dst);
		if (noBranch == nullptr)
		{
			return false;
		}
		//_noBranches.enqueue(noBranch); // TODO
		
		return addTransition(src, event, action, *noBranch);
	}
	bool addTransition(State<T>& src, int event, State<T>& dst)
	{
		static Action<T> doNothing;

		return addTransition(src, event, doNothing, dst);
	}

	void start(T context)
	{
		_currentState = _initialState;
		_currentState.entry(context);
	}

	void onEvent(int event, T context)
	{
		Transition<T>* transition = findTransition(&_currentState, event);
		if (transition == nullptr)
		{
			return;
		}

		transition->transit(context);
	}

private:
	State<T>& _initialState;
	State<T>& _currentState;
	std::map<std::pair<State<T>*, int>, Transition<T>*> _transitionMap;
	
	Transition<T>* findTransition(State<T>* src, int event)
	{
		std::pair<State<T>*, int> key = std::make_pair(src, event);
		typename std::map<std::pair<State<T>*, int>, Transition<T>*>::iterator it = _transitionMap.find(key);

		if (it == _transitionMap.end())
		{
			// not found
			return nullptr;
		}
		return it->second;
	}
};