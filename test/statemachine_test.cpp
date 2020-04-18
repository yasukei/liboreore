
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
	MOCK_METHOD1(operatorCall, void(TestStateMachineContext&));

	void operator()(TestStateMachineContext& context) { operatorCall(context); }
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
	EXPECT_CALL(_state1, entry(_))
		.Times(1);

	_statemachine.start(_context);
}

TEST_F(TestStateMachine, onEvent)
{
	_state1.addEventAction(TestEvent::even1, _action);

	{
		EXPECT_CALL(_state1, entry(_))
			.Times(1);
		_statemachine.start(_context);
	}

	{
		EXPECT_CALL(_action, operatorCall(_))
			.Times(1);
		_statemachine.onEvent(_context, TestEvent::even1);
	}
}

TEST_F(TestStateMachine, onEvent_withTransition)
{
	_state1.addEventAction(TestEvent::even1, _action);
	_statemachine.addTransition(_state1, TestEvent::even1, _state1);

	{
		EXPECT_CALL(_state1, entry(_))
			.Times(1);
		_statemachine.start(_context);
	}

	{
		InSequence inSequence;

		EXPECT_CALL(_action, operatorCall(_))
			.Times(1);
		EXPECT_CALL(_state1, exit(_))
			.Times(1);
		EXPECT_CALL(_state1, entry(_))
			.Times(1);
		_statemachine.onEvent(_context, TestEvent::even1);
	}
}

TEST_F(TestStateMachine, onEvent_multipleTransitions)
{
	_state1.addEventAction(TestEvent::even2, _action);
	_state2.addEventAction(TestEvent::even3, _action);
	_state3.addEventAction(TestEvent::even1, _action);
	_statemachine.addTransition(_state1, TestEvent::even2, _state2);
	_statemachine.addTransition(_state2, TestEvent::even3, _state3);
	_statemachine.addTransition(_state3, TestEvent::even1, _state1);

	{
		EXPECT_CALL(_state1, entry(_))
			.Times(1);
		_statemachine.start(_context);
	}

	{
		InSequence inSequence;

		EXPECT_CALL(_action, operatorCall(_))
			.Times(1);
		EXPECT_CALL(_state1, exit(_))
			.Times(1);
		EXPECT_CALL(_state2, entry(_))
			.Times(1);
		_statemachine.onEvent(_context, TestEvent::even2);
	}

	{
		InSequence inSequence;

		EXPECT_CALL(_action, operatorCall(_))
			.Times(1);
		EXPECT_CALL(_state2, exit(_))
			.Times(1);
		EXPECT_CALL(_state3, entry(_))
			.Times(1);
		_statemachine.onEvent(_context, TestEvent::even3);
	}

	{
		InSequence inSequence;

		EXPECT_CALL(_action, operatorCall(_))
			.Times(1);
		EXPECT_CALL(_state3, exit(_))
			.Times(1);
		EXPECT_CALL(_state1, entry(_))
			.Times(1);
		_statemachine.onEvent(_context, TestEvent::even1);
	}	
}
