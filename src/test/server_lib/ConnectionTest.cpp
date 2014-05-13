/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"
#include "Connection.h"
#include "IoHarbour.h"

#include <thread>
#include <functional>

namespace {

using namespace ships;
using namespace boost::asio;

struct ConnectionMock : public Connection {

	ConnectionMock(std::shared_ptr<IoHarbour> harbour)
	: Connection(harbour), accept_(0), connect_(0), send_(0), receive_(0), timer_(0), error_(0) {};
	virtual ~ConnectionMock() = default;

	virtual void onAccept(const std::string& host, uint16_t port) {++accept_;};
	virtual void onConnect(const std::string& host, uint16_t port) {++connect_;};
	virtual void onSend(const std::vector<uint8_t>& buffer) {++send_;};
	virtual void onReceive(std::vector<uint8_t>& buffer) {++receive_;};
	virtual void onTimer(const milliseconds& delta) {++timer_;};
	virtual void onError(const boost::system::error_code& error) {++error_;};

	int accept_, connect_, send_, receive_, timer_, error_;
};

class ConnectionTest : public ::testing::Test {
protected:
	ConnectionTest() : harbour(new IoHarbour()) {};
	~ConnectionTest() {};
	virtual void SetUp() {

		thread = std::shared_ptr<std::thread>(new std::thread([this]() {harbour->run();}));
		connection = std::shared_ptr<ConnectionMock>(new ConnectionMock(harbour));
	};
	virtual void TearDown() {

		harbour->stop();
		thread->join();
	};

	std::shared_ptr<IoHarbour> harbour;
	std::shared_ptr<std::thread> thread;
	std::shared_ptr<ConnectionMock> connection;

};

class EmptyConnectionTest : public ::testing::Test {
protected:
	EmptyConnectionTest() : harbour(new IoHarbour()) {};
	~EmptyConnectionTest() {};
	virtual void SetUp() {};
	virtual void TearDown() {};

	std::shared_ptr<IoHarbour> harbour;

};

TEST_F(EmptyConnectionTest, CtorDtorTest) {

	ConnectionMock connection(harbour);
	ASSERT_FALSE(connection.hasError());
	ASSERT_EQ(connection.getHarbour().get(), harbour.get());
	ASSERT_EQ(connection.getReceiveBufferSize(), 4096);
	connection.setReceiveBufferSize(2);
	ASSERT_EQ(connection.getReceiveBufferSize(), 2);
	ASSERT_EQ(connection.getTimerInterval(), 1000);
	connection.setTimerInterval(10);
	ASSERT_EQ(connection.getTimerInterval(), 10);
}

TEST_F(EmptyConnectionTest, EmptyConnectTest) {

	std::shared_ptr<ConnectionMock> connection(new ConnectionMock(harbour));

	// A connection to localhost should always work
	// but without an io_service running there is nothing to pick it up
	connection->connect("127.0.0.1", 8080);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	EXPECT_EQ(connection->error_, 0);
	EXPECT_EQ(connection->connect_, 0);
}

TEST_F(ConnectionTest, ConnectTest) {

	// A connection to Google should always work
	connection->connect("www.google.com", 80);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	EXPECT_EQ(connection->error_, 0);
	EXPECT_EQ(connection->connect_, 1);

	// The localhost should work, too.
	connection->connect("127.0.0.1", 8080);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	EXPECT_EQ(connection->error_, 0);
	EXPECT_EQ(connection->connect_, 2);
}

}  // namespace



