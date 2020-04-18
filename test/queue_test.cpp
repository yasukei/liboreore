
#include "util/queue.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class TestQueue : public testing::Test
{
public:

protected:
	virtual void SetUp()
	{
		_elem1 = 1;
		_elem2 = 2;
		_elem3 = 3;
	}
	virtual void TearDown()
	{
	}

	util::Queue<int> _queue;
	int _elem1;
	int _elem2;
	int _elem3;
};

TEST_F(TestQueue, empty)
{
	int dequeuedElem;

	EXPECT_FALSE(_queue.dequue(&dequeuedElem));
}

TEST_F(TestQueue, enque_deque_1)
{
	int dequeuedElem;

	_queue.enqueue(_elem1);

	EXPECT_TRUE(_queue.dequue(&dequeuedElem));
	EXPECT_EQ(_elem1, dequeuedElem);
}

TEST_F(TestQueue, enque_deque_2)
{
	int dequeuedElem;

	_queue.enqueue(_elem1);
	_queue.enqueue(_elem2);

	EXPECT_TRUE(_queue.dequue(&dequeuedElem));
	EXPECT_EQ(_elem1, dequeuedElem);
	EXPECT_TRUE(_queue.dequue(&dequeuedElem));
	EXPECT_EQ(_elem2, dequeuedElem);
}

TEST_F(TestQueue, enque_deque_3)
{
	int dequeuedElem;

	_queue.enqueue(_elem1);
	_queue.enqueue(_elem2);
	_queue.enqueue(_elem3);

	EXPECT_TRUE(_queue.dequue(&dequeuedElem));
	EXPECT_EQ(_elem1, dequeuedElem);
	EXPECT_TRUE(_queue.dequue(&dequeuedElem));
	EXPECT_EQ(_elem2, dequeuedElem);
	EXPECT_TRUE(_queue.dequue(&dequeuedElem));
	EXPECT_EQ(_elem3, dequeuedElem);
}
