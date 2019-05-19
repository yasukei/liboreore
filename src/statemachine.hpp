#pragma once

#include <vector>

// << Event							(= [NoCondition] Event / NoAction)
// << Event / Action
// << [Condition] Event
// << [Condition] Event / Action

// [TODO]
// - nested statemachine
// - polymorphism for State.onEvent without switch-case (= arbitary onEvent method such as onTick)
// - coverage
// - performance

// [DONE]
// - application specific context (especially arguments for each event)
// - branch in transition
// - ctest

typedef int Event;

template <typename T>
class Action
{
	public:
		virtual ~Action() {}
		virtual void operator()(T context) { (void)context; }
};

template <typename T>
class GuardCondition
{
	public:
		virtual ~GuardCondition() {}
		virtual bool isSatisfied(T context) { (void)context; return true; }
};

template <typename T>
class State
{
	public:
		virtual ~State() {}
		virtual void enter(T context) { (void)context; }
		virtual void exit(T context) { (void)context; }
		virtual void onEvent(Event event, T context) { (void)event; (void)context; }
};

template <typename T>
class Branch
{
	public:
		virtual ~Branch() {}
		virtual State<T>& getDstState(T context) = 0;
};

template <typename T>
class NoBranch : public Branch<T>
{
	public:
		NoBranch(State<T>& dstState) : dstState_(dstState) {}
		State<T>& getDstState(T context) { (void)context; return dstState_; }

	private:
		State<T>& dstState_;
};

template <typename T>
class Transition
{
	public:
		Transition(State<T>& src, State<T>& dst, Event event, GuardCondition<T>& guardCondition, Action<T>& action) :
			src_(src),
			noBranch_(dst),
			branch_(noBranch_),
			event_(event),
			guardCondition_(guardCondition),
			action_(action)
		{
		}
		Transition(State<T>& src, Branch<T>& branch, Event event, GuardCondition<T>& guardCondition, Action<T>& action) :
			src_(src),
			noBranch_(src),
			branch_(branch),
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
			action_(context);
			State<T>& dst = branch_.getDstState(context);
			dst.enter(context);
			return dst;
		}

	private:
		State<T>& src_;
		NoBranch<T> noBranch_;
		Branch<T>& branch_;
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
			currentState_(&initialState),
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

		void addTransition(State<T>& src, State<T>& dst, Event event)
		{
			addTransition(src, dst, event, noGuardCondition_, noAction_);
		}
		void addTransition(State<T>& src, State<T>& dst, Event event, GuardCondition<T>& guardCondition)
		{
			addTransition(src, dst, event, guardCondition, noAction_);
		}
		void addTransition(State<T>& src, State<T>& dst, Event event, Action<T>& action)
		{
			addTransition(src, dst, event, noGuardCondition_, action);
		}
		void addTransition(State<T>& src, State<T>& dst, Event event, GuardCondition<T>& guardCondition, Action<T>& action)
		{
			Transition<T>* transition = new Transition<T>(src, dst, event, guardCondition, action);
			transitions_.push_back(transition);
		}
		void addTransition(State<T>& src, Branch<T>& branch, Event event)
		{
			addTransition(src, branch, event, noGuardCondition_, noAction_);
		}
		void addTransition(State<T>& src, Branch<T>& branch, Event event, GuardCondition<T>& guardCondition)
		{
			addTransition(src, branch, event, guardCondition, noAction_);
		}
		void addTransition(State<T>& src, Branch<T>& branch, Event event, Action<T>& action)
		{
			addTransition(src, branch, event, noGuardCondition_, action);
		}
		void addTransition(State<T>& src, Branch<T>& branch, Event event, GuardCondition<T>& guardCondition, Action<T>& action)
		{
			Transition<T>* transition = new Transition<T>(src, branch, event, guardCondition, action);
			transitions_.push_back(transition);
		}
		void start(T context)
		{
			currentState_ = &initialState_;
			currentState_->enter(context);
		}
		void onEvent(Event event, T context)
		{
			currentState_->onEvent(event, context);
			for(Transition<T>* transition : transitions_)
			{
				if(transition->canTransit(*currentState_, event, context))
				{
					currentState_ = &(transition->transit(context));
					break;
				}
			}
		}

	private:
		State<T>& initialState_;
		State<T>* currentState_;
		std::vector<Transition<T>*> transitions_;

		GuardCondition<T> noGuardCondition_;
		Action<T> noAction_;
};

