/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "Gameboard.h"

class GameboardTest : public ::testing::Test {
protected:
	GameboardTest() {};
	~GameboardTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(GameboardTest, ConstructorTest) {
	Gameboard gameboard(10);
	ASSERT_EQ(gameboard.getSize(),100);
}
TEST_F(GameboardTest, HitTest) {
	Gameboard gameboard(4);

	gameboard.hit(1,1);
}
TEST_F(GameboardTest, GetFieldTest) {
	Gameboard gameboard(4);

	gameboard.hit(1,1);
}




