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
using namespace ships;
namespace ships {
class Connection {};

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

	typedef std::shared_ptr<Connection> ConnectionPtr;
	typedef std::shared_ptr<ConnectionObserverMock> ObserverPtr;

};

TEST_F(ConnectionPoolTest, CtorDtorTest) {

	ConnectionPool connectionPool;
	ASSERT_EQ(connectionPool.size(), 0);
	ASSERT_EQ(connectionPool.getConnsToSignal(), 1);
}

TEST_F(ConnectionPoolTest, AddConnectionTest) {

	ConnectionPool connectionPool;
	ConnectionPtr connection(new Connection());

	connectionPool.addConnection(connection);
	ASSERT_EQ(connectionPool.size(), 1);

	ASSERT_EQ(connectionPool.getConnection(), connection);
	ASSERT_EQ(connectionPool.size(), 0);

	connectionPool.addConnection(ConnectionPtr(new Connection()));
	connectionPool.addConnection(ConnectionPtr(new Connection()));
	ASSERT_EQ(connectionPool.size(), 2);
	ASSERT_EQ(connectionPool.getConnection(2).size(), 2);
	ASSERT_EQ(connectionPool.size(), 0);
}

TEST_F(ConnectionPoolTest, SignalTest) {

	ConnectionPool connectionPool;

	ObserverPtr observer(new ConnectionObserverMock());
	EXPECT_CALL(*observer, signal()).Times(1);

	connectionPool.registerConnectionObserver(observer);
	connectionPool.addConnection(ConnectionPtr(new Connection()));
	connectionPool.getConnection();

	EXPECT_CALL(*observer, signal()).Times(0);
	connectionPool.setConnsToSignal(2);
	connectionPool.addConnection(ConnectionPtr(new Connection()));

	EXPECT_CALL(*observer, signal()).Times(1);
	connectionPool.addConnection(ConnectionPtr(new Connection()));
}




