
#include "util/listener.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockListener : public util::Listener<int>
{
public:
	MOCK_METHOD1(notify, void(int));
};

class TestListener : public testing::Test
{
public:

protected:
	virtual void SetUp()
	{
	}
	virtual void TearDown()
	{
	}

	util::Listeners<int> _listeners;
	MockListener _listener1;
	MockListener _listener2;
	int _dummy;
};

TEST_F(TestListener, empty)
{
	_listeners.notify(_dummy);
}

TEST_F(TestListener, singleListener)
{
	_listeners.addListener(_listener1);

	EXPECT_CALL(_listener1, notify(_dummy))
		.Times(1);
	_listeners.notify(_dummy);
}

TEST_F(TestListener, multipleListeners)
{
	_listeners.addListener(_listener1);
	_listeners.addListener(_listener2);

	EXPECT_CALL(_listener1, notify(_dummy))
		.Times(1);
	EXPECT_CALL(_listener2, notify(_dummy))
		.Times(1);
	_listeners.notify(_dummy);
}
