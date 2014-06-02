/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ConnectionPool.h"
#include "ConnectionObserver.h"

#include <memory>

using namespace testing;
using namespace net;

namespace net {
class ProtobufConnection {};

struct ConnectionObserverMock : public ConnectionObserver {

	MOCK_METHOD0(signal, void(void));
};

}

class ConnectionPoolTest : public ::testing::Test {
protected:
	ConnectionPoolTest() {};
	~ConnectionPoolTest() {};
	virtual void SetUp() {};
	virtual void TearDown() {};

	typedef std::shared_ptr<ProtobufConnection> ConnectionPtr;
	typedef std::shared_ptr<ConnectionObserverMock> ObserverPtr;

};

TEST_F(ConnectionPoolTest, CtorDtorTest) {

	ConnectionPool connectionPool;
	ASSERT_EQ(connectionPool.size(), 0);
	ASSERT_EQ(connectionPool.getConnsToSignal(), 1);
}

TEST_F(ConnectionPoolTest, AddConnectionTest) {

	ConnectionPool connectionPool;
	ConnectionPtr connection(new ProtobufConnection());

	connectionPool.addConnection(connection);
	ASSERT_EQ(connectionPool.size(), 1);

	ASSERT_EQ(connectionPool.getConnection(), connection);
	ASSERT_EQ(connectionPool.size(), 0);

	connectionPool.addConnection(ConnectionPtr(new ProtobufConnection()));
	connectionPool.addConnection(ConnectionPtr(new ProtobufConnection()));
	ASSERT_EQ(connectionPool.size(), 2);
	ASSERT_EQ(connectionPool.getConnection(2).size(), 2);
	ASSERT_EQ(connectionPool.size(), 0);
}

TEST_F(ConnectionPoolTest, SignalTest) {

	ConnectionPool connectionPool;

	ObserverPtr observer(new ConnectionObserverMock());
	EXPECT_CALL(*observer, signal()).Times(1);

	connectionPool.registerConnectionObserver(observer);
	connectionPool.addConnection(ConnectionPtr(new ProtobufConnection()));
	connectionPool.getConnection();

	EXPECT_CALL(*observer, signal()).Times(0);
	connectionPool.setConnsToSignal(2);
	connectionPool.addConnection(ConnectionPtr(new ProtobufConnection()));

	EXPECT_CALL(*observer, signal()).Times(1);
	connectionPool.addConnection(ConnectionPtr(new ProtobufConnection()));
}




