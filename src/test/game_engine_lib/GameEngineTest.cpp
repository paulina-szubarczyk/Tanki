/*
 * GameEngineTest.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: paulina
 */

#include "GamesManager.h"
#include "gtest/gtest.h"
using namespace game;
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
