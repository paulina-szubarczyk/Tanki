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

TEST_F(GameManagerTest, updateShipsToAddTest){
	GameManager manager;
	for(int i=1; i<6; i++)
			manager.getShipsQuantity().insert(std::pair<int,int>(i,i));
	manager.updateShipsToAdd();
	std::cout<<manager.getShipsToAdd();
	std::string test = "1 1\n2 2\n3 3\n4 4\n5 5\n";
	std::map<int,int>::iterator it;

	ASSERT_EQ(test,manager.getShipsToAdd());
}


