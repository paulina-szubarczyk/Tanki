/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"
#include "IoHarbour.h"

#include <thread>
#include <functional>
#include <chrono>

namespace {

using namespace net;
using namespace boost::asio;

class IoHarbourTest : public ::testing::Test {
protected:
	IoHarbourTest() {};
	~IoHarbourTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};

};

TEST_F(IoHarbourTest, CtorDtorTest) {

	IoHarbour ioHarbour;
}

TEST_F(IoHarbourTest, GetServiceTest) {

	IoHarbour ioHarbour;
	boost::asio::io_service& service = ioHarbour.getService();
}

TEST_F(IoHarbourTest, StopServiceTest) {

	IoHarbour ioHarbour;
	EXPECT_FALSE(ioHarbour.hasStopped());
	ioHarbour.stop();
	EXPECT_TRUE(ioHarbour.hasStopped());
}

TEST_F(IoHarbourTest, ResetTest) {

	IoHarbour ioHarbour;
	ioHarbour.stop();
	ASSERT_TRUE(ioHarbour.hasStopped());
	ioHarbour.reset();
	ASSERT_FALSE(ioHarbour.hasStopped());
}

TEST_F(IoHarbourTest, ConstantRunTest) {

	IoHarbour ioHarbour;
	bool running = false;
	std::thread thread([&]() { running = true; ioHarbour.run(); });
	std::thread timedJoin([&]() { thread.join(); running = false; });
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	EXPECT_TRUE(running);
	ioHarbour.stop();
	timedJoin.detach();
	thread.detach();
}

TEST_F(IoHarbourTest, EmptyPollTest) {

	IoHarbour ioHarbour;
	bool running = false;
	std::thread thread([&]() { running = true; ioHarbour.poll(); running = false; });
	thread.join();
	ASSERT_FALSE(running);
	ioHarbour.stop();
}

TEST_F(IoHarbourTest, DispatchPollTest) {

	bool executed = false;
	auto fun = [&executed]() { executed = true; };
	IoHarbour ioHarbour;
	ioHarbour.dispatch(fun);
	ioHarbour.poll();
	ASSERT_TRUE(executed);
}

TEST_F(IoHarbourTest, PostPollTest) {

	bool executed = false;
	auto fun = [&executed]() { executed = true; };
	IoHarbour ioHarbour;
	ioHarbour.post(fun);
	ioHarbour.poll();
	ASSERT_TRUE(executed);
}

}  // namespace



