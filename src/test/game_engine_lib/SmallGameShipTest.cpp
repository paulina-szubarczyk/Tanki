///*
// * StatekTest.cpp
// *
// *  Created on: May 10, 2014
// *      Author: paulina
// */
#include "gtest/gtest.h"
#include "SmallGameShip.h"

class SmallGameShipTest : public ::testing::Test {
protected:
	SmallGameShipTest() {};
	~SmallGameShipTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};
TEST_F(SmallGameShipTest, ConstructorTest){
	SmallGameShip ship;
	EXPECT_EQ(ship.getState(),GameShip::ShipState::FLOAT);
	EXPECT_EQ(ship.getSize(),1);
}

TEST_F(SmallGameShipTest, GameShipStateTest){

	SmallGameShip ship;
	EXPECT_EQ(ship.getState(), SmallGameShip::ShipState::FLOAT);
	ship.hit();
	EXPECT_EQ(ship.getState(), SmallGameShip::ShipState::SUNK);
}

TEST_F(SmallGameShipTest, CreateShipTest){
	std::shared_ptr<SmallGameShip> ship(dynamic_cast<SmallGameShip*>(SmallGameShip::createSmallGameShip(0)));
	EXPECT_EQ(ship->getState(),GameShip::ShipState::FLOAT);
	EXPECT_EQ(ship->getSize(),1);
}

