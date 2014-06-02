/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Acceptor.h"
#include "IoHarbour.h"
#include "ProtobufConnection.h"

#include <thread>
#include <functional>

namespace {

using namespace ships;
using namespace boost::asio;
using namespace testing;

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

struct AcceptorMock : public Acceptor {
	AcceptorMock(std::shared_ptr<IoHarbour> harbour)
	: Acceptor(harbour), accept_(0), timer_(0), error_(0), shouldAccept_(true) {};
	virtual ~AcceptorMock() = default;

	bool onAccept(std::shared_ptr<ProtobufConnection> connection,
				const std::string & host, uint16_t port) override {++accept_; return shouldAccept_;};
	void onTimer(const milliseconds& delta) override {++timer_;};
	void onError(const boost::system::error_code & error) override {++error_;};

	bool shouldAccept_;
	int accept_, timer_, error_;
};

/**
 * Mock
 */
class ConnectionMock : public ProtobufConnection {
public:

		ConnectionMock(std::shared_ptr<IoHarbour> harbour) : ProtobufConnection(harbour) {};
		virtual ~ConnectionMock() = default;

		MOCK_METHOD2(onAccept, void(const std::string& host, uint16_t port));
		MOCK_METHOD2(onConnect, void(const std::string& host, uint16_t port));
		MOCK_METHOD1(onSend, void(const std::vector<uint8_t> & buffer));
		MOCK_METHOD1(onReceive, void(std::vector<uint8_t> & buffer));
		MOCK_METHOD1(onTimer, void(const milliseconds& delta));
		MOCK_METHOD1(onError, void(const boost::system::error_code & error));
};

/**
 * Below tests use a previously tested IoHarbour class
 */
class AcceptorTest : public ::testing::Test {
protected:
	AcceptorTest() : harbour(new IoHarbour()) {};
	~AcceptorTest() {};
	virtual void SetUp() {

		thread = std::shared_ptr<std::thread>(new std::thread([this]() {harbour->run();}));
	};
	virtual void TearDown() {

		harbour->stop();
		thread->join();
	};

	std::shared_ptr<std::thread> thread;
	typedef std::shared_ptr<IoHarbour> HarbourType;
	HarbourType harbour;
	typedef std::shared_ptr<AcceptorMock> AcceptorPtr;
	typedef std::shared_ptr<ConnectionMock> ConnectionPtr;
};

TEST_F(AcceptorTest, CtorDtorTest) {

	AcceptorMock acceptor(harbour);
	ASSERT_EQ(acceptor.accept_, 0);
	ASSERT_EQ(acceptor.timer_, 0);
	ASSERT_EQ(acceptor.error_, 0);
	ASSERT_EQ(acceptor.shouldAccept_, true);
	ASSERT_FALSE(acceptor.hasError());
	ASSERT_EQ(acceptor.getHarbour(), harbour);
	ip::tcp::acceptor& a = acceptor.getAcceptor();
	strand st = acceptor.getStrand();
	ASSERT_EQ(acceptor.getTimerInterval(), 1000);
	acceptor.setTimerInterval(100);
	ASSERT_EQ(acceptor.getTimerInterval(), 100);
}

TEST_F(AcceptorTest, TimerTest) {

	AcceptorPtr acceptor(new AcceptorMock(harbour));
	acceptor->setTimerInterval(100);
	sleep_for(milliseconds(100));
	EXPECT_EQ(acceptor->timer_, 0);
	acceptor->listen("localhost", 8080);
	sleep_for(milliseconds(110));
	EXPECT_EQ(acceptor->timer_, 1);
	acceptor->setTimerInterval(5);
	sleep_for(milliseconds(150));
	EXPECT_GE(acceptor->timer_, 5);
	ASSERT_EQ(acceptor->error_, 0);
	acceptor->stop();
}

TEST_F(AcceptorTest, ListenTest) {

	AcceptorPtr acceptor(new AcceptorMock(harbour));
	ip::tcp::acceptor& a = acceptor->getAcceptor();
	ASSERT_FALSE(a.is_open());
	acceptor->listen("127.0.0.1", 8081);
	ASSERT_TRUE(a.is_open());
	ASSERT_EQ(a.local_endpoint().address().to_string(), "127.0.0.1");
	ASSERT_EQ(a.local_endpoint().port(), 8081);
	acceptor->stop();
}

TEST_F(AcceptorTest, StopTest) {

	AcceptorPtr acceptor(new AcceptorMock(harbour));
	ASSERT_NO_THROW(acceptor->listen("127.0.0.1", 8082));
	sleep_for(milliseconds(100));
	ASSERT_ANY_THROW(acceptor->listen("127.0.0.1", 8082));
	acceptor->stop();
	sleep_for(milliseconds(100));
	ASSERT_NO_THROW(acceptor->listen("127.0.0.1", 8082));
	acceptor->stop();
}

TEST_F(AcceptorTest, AcceptTest) {

	AcceptorPtr acceptor(new AcceptorMock(harbour));
	ConnectionPtr connection(new ConnectionMock(harbour));
	ConnectionPtr incoming(new ConnectionMock(harbour));

	EXPECT_CALL(*connection, onAccept("127.0.0.1", 8086)).Times(AtLeast(1));
	EXPECT_CALL(*connection, onError(_)).Times(0);

	EXPECT_CALL(*incoming, onError(_)).Times(0);

	acceptor->listen("127.0.0.1", 8086);
	acceptor->accept(connection);
	incoming->connect("127.0.0.1", 8086);
}

}  // namespace



