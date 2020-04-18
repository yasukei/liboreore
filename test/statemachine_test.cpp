//#include "pch.h"

#include "util/statemachine.hpp"

#include <gtest/gtest.h>

struct Context
{
public:
    int counter;
};

class State1 : public util::State<Context&>
{
    // TODO use gmock
public:
    void entry(Context& context)
    {
        context.counter += 1;
    }
};

struct TestEvent
{
    enum
    {
        even1,
        even2,
        even3,
    };
};

TEST(TestCaseName, TestName)
{
    State1 state1;
	util::StateMachine<Context&> statemachine(state1);
    Context context;

    statemachine.addTransition(state1, TestEvent::even1, state1);
    statemachine.start(context);

	EXPECT_TRUE(false);
}
