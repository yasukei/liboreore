#include <stdio.h>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "oreore.h"
#include "statemachine.hpp"

TEST(aaa, bbb)
{
	EXPECT_TRUE(true);
}

class PrintiveState : public State<const char*>
{
	public:
		PrintiveState(const char* msg) :
			msg_(msg)
		{
		}
		void enter(const char*) { printf("%s enter\n", msg_.c_str()); }
		void exit(const char*) { printf("%s exit\n", msg_.c_str()); }

	private:
		std::string msg_;

		PrintiveState() {}
};

int dummymain(void)
{
	oreore();

	PrintiveState s1("state1");
	PrintiveState s2("state2");
	StateMachine<const char*> sm(s1);
	enum
	{
		event1,
	};

	sm.addTransision(s1, s2, event1);
	sm.start(nullptr);
	sm.onEvent(event1, nullptr);

	// << [Condition] Event / Action

	//sm += s1 -> s2 [guard] event1 / Action

	return 0;
}

