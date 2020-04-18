
#include "util/statemachine.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::_;
using testing::InSequence;

struct TestStateMachineContext
{
public:
};

class TestState : public util::State<TestStateMachineContext&>
{
public:
	MOCK_METHOD1(entry, void(TestStateMachineContext&));
	MOCK_METHOD1(exit, void(TestStateMachineContext&));
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

class TestStateMachine : public testing::Test
{
public:
	TestStateMachine() :
		_state1(),
		_statemachine(_state1),
		_context()
	{
	}

protected:
	virtual void SetUp()
	{
	}
	virtual void TearDown()
	{
	}

	TestState _state1;
	util::StateMachine<TestStateMachineContext&> _statemachine;
	TestStateMachineContext _context;
};

TEST_F(TestStateMachine, start)
{
    _statemachine.addTransition(_state1, TestEvent::even1, _state1);
	_statemachine.start(_context);
}
