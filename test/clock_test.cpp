#include <thread>
#include <chrono>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "clock.hpp"

class TestClock : public testing::Test
{
protected:
	virtual void SetUp()
	{}
	virtual void TearDown()
	{}
};

TEST_F(TestClock, _)
{
	Clock clock;

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	uint64_t milliseconds = clock.getElapsedTimeMillisec();
	uint64_t microseconds = clock.getElapsedTimeMicrosec();
	uint64_t nanoseconds = clock.getElapsedTimeNanosec();
	EXPECT_EQ(milliseconds, 10);
	EXPECT_EQ(milliseconds, microseconds / 1000);
	EXPECT_EQ(milliseconds, nanoseconds / 1000 / 1000);
}

