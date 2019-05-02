#pragma once

#include <vector>

// << Event							(= [NoCondition] Event / NoAction)
// << Event / Action
// << [Condition] Event
// << [Condition] Event / Action

// - nested statemachine
// - application specific context (especially arguments for each event)
// - State.enter/exit is Action?
// - branch in transition

typedef int Event;

template <typename T>
class Action
{
	public:
		virtual ~Action() {}
		virtual void operator()(T context) = 0;
};

template <typename T>
class GuardCondition
{
	public:
		virtual ~GuardCondition() {}
		virtual bool isSatisfied(T context) = 0;
};

template <typename T>
class State
{
	public:
		virtual ~State() {}
		virtual void enter(T context) = 0;
		virtual void exit(T context) = 0;
};

template <typename T>
class Transition
{
	public:
		Transition(State<T>& src, State<T>& dst, Event event, GuardCondition<T>& guardCondition, Action<T>& action) :
			src_(src),
			dst_(dst),
			event_(event),
			guardCondition_(guardCondition),
			action_(action)
		{
		}

		bool canTransit(State<T>& src, Event event, T context)
		{
			return &src == &src_ && event == event_ && guardCondition_.isSatisfied(context);
		}

		State<T>& transit(T context)
		{
			src_.exit(context);
			dst_.enter(context);
			return dst_;
		}

	private:
		State<T>& src_;
		State<T>& dst_;
		Event event_;
		GuardCondition<T>& guardCondition_;
		Action<T>& action_;
};

template <typename T>
class StateMachine
{
	public:
		StateMachine(State<T>& initialState) :
			initialState_(initialState),
			currentState_(initialState),
			transitions_()
		{
		}

		~StateMachine()
		{
			for(Transition<T>* transition : transitions_)
			{
				delete transition;
			}
			transitions_.clear();
		}

		void addTransision(State<T>& src, State<T>& dst, Event event)
		{
			addTransision(src, dst, event, noGuardCondition_, noAction_);
		}
		void addTransision(State<T>& src, State<T>& dst, Event event, GuardCondition<T>& guardCondition)
		{
			addTransision(src, dst, event, guardCondition, noAction_);
		}
		void addTransision(State<T>& src, State<T>& dst, Event event, Action<T>& action)
		{
			addTransision(src, dst, event, noGuardCondition_, action);
		}
		void addTransision(State<T>& src, State<T>& dst, Event event, GuardCondition<T>& guardCondition, Action<T>& action)
		{
			Transition<T>* transition = new Transition<T>(src, dst, event, guardCondition, action);
			transitions_.push_back(transition);
		}
		void start(T context)
		{
			currentState_ = initialState_;
			currentState_.enter(context);
		}
		void onEvent(Event event, T context)
		{
			for(Transition<T>* transition : transitions_)
			{
				if(transition->canTransit(currentState_, event, context))
				{
					currentState_ = transition->transit(context);
					break;
				}
			}
		}

	private:
		State<T>& initialState_;
		State<T>& currentState_;
		std::vector<Transition<T>*> transitions_;

		class NoGuardCondition : public GuardCondition<T>
		{
			public:
				bool isSatisfied(T /* context */) { return true; }
		}noGuardCondition_;

		class NoAction : public Action<T>
		{
			public:
				void operator()(T /* context */) {}
		}noAction_;
};

