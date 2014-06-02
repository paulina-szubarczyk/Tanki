///*
// * StatekTest.cpp
// *
// *  Created on: May 10, 2014
// *      Author: paulina
// */
#include "gtest/gtest.h"

class GamePlayerBuilderTest : public ::testing::Test {
protected:
	GamePlayerBuilderTest() {};
	~GamePlayerBuilderTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F( GamePlayerBuilderTest, ConstructorTest){ }
TEST_F( GamePlayerBuilderTest, createGamePlayeTest){ }
TEST_F( GamePlayerBuilderTest, addPlayerGameboardTest){ }
TEST_F( GamePlayerBuilderTest, addPlayerShipsTest){ }
TEST_F( GamePlayerBuilderTest, addPlayerShipTest){ }
TEST_F( GamePlayerBuilderTest, configPlayerFieldsUpdaterTest){ }


