/*
 * GameEngineTest.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: paulina
 */

#include "GameEngine.h"
#include "gtest/gtest.h"

class GameEngineTest : public ::testing::Test {
protected:
	GameEngineTest() {};
	~GameEngineTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(GameEngineTest, ConstructorTest){ }

TEST_F(GameEngineTest, CreateGameTest){ }

TEST_F(GameEngineTest, CreatePlayerTest){ }
