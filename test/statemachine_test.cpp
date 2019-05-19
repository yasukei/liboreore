#include <stdio.h>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "statemachine.hpp"

enum
{
	event1,
	event2,
};

class PrintiveState : public State<const char*>
{
	public:
		PrintiveState(const char* msg) :
			msg_(msg)
		{
		}
		void enter(const char*) { printf("%s enter\n", msg_.c_str()); }
		void exit(const char*) { printf("%s exit\n", msg_.c_str()); }
		void onEvent(Event event, const char*)
		{
			switch(event)
			{
				case event2:
					printf("%s event2\n", msg_.c_str());
					break;
				default:
					break;
			}
		}

	private:
		std::string msg_;

		PrintiveState() {}
};

int dummymain(void)
{
	PrintiveState s1("state1");
	PrintiveState s2("state2");
	StateMachine<const char*> sm(s1);

	// << [Condition] Event / Action
	//sm += s1 -> s2 [guard] | event1 / Action
	//sm::s1->s2|event1
	sm.addTransition(s1, s2, event1);
	//sm.addTransition(s2, s2, event2);

	sm.start(nullptr);
	sm.onEvent(event1, nullptr);
	sm.onEvent(event2, nullptr);

	return 0;
}

TEST(aaa, bbb)
{
	dummymain();
	EXPECT_TRUE(true);
}

