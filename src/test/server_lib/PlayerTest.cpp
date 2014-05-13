/*
 * packedmessagetest.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: Adam Kosiorek
 */
#include "gtest/gtest.h"
#include "Player.h"

namespace {

using namespace ships;

class PlayerTest : public ::testing::Test {
protected:
	PlayerTest() {};
	~PlayerTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};

};

TEST_F(PlayerTest, CtorDtorTest) {

	Player player;
}

TEST_F(PlayerTest, AddConnectionTest) {

	Player player;
	EXPECT_EQ(player.getConnections().size(), 0);

	player.addConnection(Connection());
	EXPECT_EQ(player.getConnections().size(), 1);
}


}  // namespace



