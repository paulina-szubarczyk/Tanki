/*
 * GameManagerTest.cpp
 *
 *  Created on: May 30, 2014
 *      Author: klis
 */

#include "gtest/gtest.h"
#include "GameManager.h"
#include <iostream>

class GameManagerTest : public ::testing::Test {
protected:
	GameManagerTest() {};
	~GameManagerTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(GameManagerTest, decreaseShipsQuantityTest){
	std::shared_ptr<GameManager> manager(new GameManager);
	ASSERT_EQ(manager->getRemainingShips(5),1);
	manager->decreaseShipsQuantity(5);
	ASSERT_EQ(manager->getRemainingShips(5),0);

}

TEST_F(GameManagerTest, getSmallestSizeTest){
	std::shared_ptr<GameManager> manager(new GameManager);
	ASSERT_EQ(manager->getRemainingShips(5),1);
	ASSERT_EQ(manager->getSmallestSize(),2);

}
TEST_F(GameManagerTest, checkReadyTest){
	std::shared_ptr<GameManager> manager(new GameManager);
	manager->decreaseShipsQuantity(5);
	ASSERT_FALSE(manager->checkReady());
	for(int i = 0; i < 3; i++){
		manager->decreaseShipsQuantity(2);
		ASSERT_FALSE(manager->checkReady());
	}
	for(int i = 0; i < 2; i++){
			ASSERT_FALSE(manager->checkReady());
			manager->decreaseShipsQuantity(3);
		}
	ASSERT_TRUE(manager->checkReady());

}


