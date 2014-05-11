///*
// * StatekTest.cpp
// *
// *  Created on: May 10, 2014
// *      Author: paulina
// */
#include "gtest/gtest.h"
#include "BigGameShip.h"
#include "SmallGameShip.h"
#include "Field.h"

class BigGameShipTest : public ::testing::Test {
protected:
	BigGameShipTest() {};
	~BigGameShipTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};
TEST_F(BigGameShipTest, ConstructorTest){
	BigGameShip ship;
	EXPECT_EQ(ship.getState(), GameShip::ShipState::FLOAT);
	EXPECT_EQ(ship.getSize(),0);
}

TEST_F(BigGameShipTest, AddShipsTest){
	SmallGameShip ship;
	BigGameShip bigship;
//	bigship.addShip(ship);
//	EXPECT_EQ(ship.getSize(),1);
}
TEST_F(BigGameShipTest, GameShipStateTest){

//	SmallGameShip ship;
//	BigGameShip bigship;
//	bigship.addShip(ship);
//
//	ship.changeState(SmallGameShip::ShipState::HIT);
//	EXPECT_EQ(bigship.getState(), SmallGameShip::ShipState::SUNK);
}


