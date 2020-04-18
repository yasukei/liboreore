
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

class TestAction : public util::Action<TestStateMachineContext&>
{
public:
	MOCK_METHOD1(function, void(TestStateMachineContext&));

	void operator()(TestStateMachineContext& context) { function(context); }
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
		_state2(),
		_state3(),
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
	TestState _state2;
	TestState _state3;
	TestAction _action;
	util::StateMachine<TestStateMachineContext&> _statemachine;
	TestStateMachineContext _context;
};

TEST_F(TestStateMachine, start)
{
	// start
	EXPECT_CALL(_state1, entry(_))
		.Times(1);

	_statemachine.start(_context);
}

TEST_F(TestStateMachine, onEvent)
{
	{
		InSequence inSequence;

		// start
		EXPECT_CALL(_state1, entry(_))
			.Times(1);

		// on TestEvent::even1
		EXPECT_CALL(_action, function(_))
			.Times(1);
	}

	_state1.addEventAction(TestEvent::even1, _action);
	_statemachine.start(_context);
	_statemachine.onEvent(_context, TestEvent::even1);
}

TEST_F(TestStateMachine, onEvent_SelfTransition)
{
	{
		InSequence inSequence;

		// start
		EXPECT_CALL(_state1, entry(_))
			.Times(1);

		// on TestEvent::even1
		EXPECT_CALL(_state1, exit(_))
			.Times(1);
		EXPECT_CALL(_state1, entry(_))
			.Times(1);
	}

	_statemachine.addTransition(_state1, TestEvent::even1, _state1);
	_statemachine.start(_context);
	_statemachine.onEvent(_context, TestEvent::even1);
}

TEST_F(TestStateMachine, hoge)
{
	//_statemachine.addTransition(_testState1, TestEvent::even1, _testState1);
	//_statemachine.addTransition(_testState1, TestEvent::even2, _testState2);
	//_statemachine.addTransition(_testState1, TestEvent::even3, _testState3);
	//_statemachine.addTransition(_testState2, TestEvent::even2, _testState2);
	//_statemachine.addTransition(_testState2, TestEvent::even3, _testState3);
	//_statemachine.addTransition(_testState3, TestEvent::even1, _testState1);
	//_statemachine.addTransition(_testState3, TestEvent::even3, _testState3);
	//_statemachine.start(_context);

	//EXPECT_CALL(testState1, entry(_))
	//	.Times(1);
}
