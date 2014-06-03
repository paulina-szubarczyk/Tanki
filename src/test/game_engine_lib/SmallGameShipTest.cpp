///*
// * StatekTest.cpp
// *
// *  Created on: May 10, 2014
// *      Author: paulina
// */
#include "gtest/gtest.h"
#include "SmallShip.h"
using namespace game;
class SmallGameShipTest : public ::testing::Test {
protected:
	SmallGameShipTest() {};
	~SmallGameShipTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};
TEST_F(SmallGameShipTest, ConstructorTest){
	SmallShip ship;
	EXPECT_EQ(ship.getState(),IShip::ShipState::FLOAT);
	EXPECT_EQ(ship.getSize(),1);
}

TEST_F(SmallGameShipTest, GameShipStateTest){

	SmallShip ship;
	EXPECT_EQ(ship.getState(), SmallShip::ShipState::FLOAT);
	ship.hit();
	EXPECT_EQ(ship.getState(), SmallShip::ShipState::SUNK);
}

TEST_F(SmallGameShipTest, CreateShipTest){
	std::shared_ptr<SmallShip> ship(dynamic_cast<SmallShip*>(SmallShip::createSmallGameShip(0)));
	EXPECT_EQ(ship->getState(),IShip::ShipState::FLOAT);
	EXPECT_EQ(ship->getSize(),1);
}

