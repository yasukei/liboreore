#include <stdio.h>
#include "oreore.h"
#include "statemachine.hpp"

class State1 : public State
{
	public:
		void entry() { printf("State1 entry\n"); }
		void exit() { printf("State1 exit\n"); }
};

class State2 : public State
{
	public:
		void entry() { printf("State2 entry\n"); }
		void exit() { printf("State2 exit\n"); }
};

int main(void)
{
	oreore();

	State1 s1;
	State2 s2;
	StateMachine sm(&s1);

	sm.start();
	sm.addTransision(&s1, &s2, 1);
	sm.onEvent(1);

	return 0;
}

