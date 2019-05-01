#pragma once

#include <vector>

// << Event							(= [NoCondition] Event / NoAction)
// << Event / Action
// << [Condition] Event
// << [Condition] Event / Action

typedef int Event;

class Action
{
	public:
		virtual ~Action() {}
		virtual void operator()() = 0;
};

class State
{
	public:
		virtual ~State() {}
		virtual void entry() = 0;
		virtual void exit() = 0;
};

class GuardCondition
{
	public:
		virtual ~GuardCondition() {}
		virtual bool isSatisfied() { return true; };

		static GuardCondition* getTrueCondition()
		{
			return &instance_;
		}

	private:
		static GuardCondition instance_;
};

GuardCondition GuardCondition::instance_;

class Transition
{
	public:
		Transition(State* src, State* dst, Event event, GuardCondition* guardCondition = GuardCondition::getTrueCondition()) :
			src_(src),
			dst_(dst),
			event_(event),
			guardCondition_(guardCondition)
		{
		}
		bool canTransit(State* src, Event event)
		{
			return src == src_ && event == event_ && guardCondition_->isSatisfied();
		}
		State* transit()
		{
			src_->exit();
			dst_->entry();
			return dst_;
		}

	private:
		State* src_;
		State* dst_;
		Event event_;
		GuardCondition* guardCondition_;
};

class StateMachine
{
	public:
		StateMachine(State* initialState) :
			initialState_(initialState),
			currentState_(nullptr),
			transitions_()
		{
		}

		~StateMachine()
		{
			for(Transition* transition : transitions_)
			{
				delete transition;
			}
			transitions_.clear();
		}

		void addTransision(State* src, State* dst, Event event)
		{
			Transition* transition = new Transition(src, dst, event);
			transitions_.push_back(transition);
		}
		void start()
		{
			currentState_ = initialState_;
			currentState_->entry();
		}
		void onEvent(Event event)
		{
			for(Transition* transition : transitions_)
			{
				if(transition->canTransit(currentState_, event))
				{
					currentState_ = transition->transit();
					break;
				}
			}
		}

	private:
		State* initialState_;
		State* currentState_;
		std::vector<Transition*> transitions_;
};

