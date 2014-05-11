///*
// * StatekTest.cpp
// *
// *  Created on: May 10, 2014
// *      Author: paulina
// */
#include "gtest/gtest.h"
#include "SmallGameShip.h"
#include "Field.h"

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
TEST_F(SmallGameShipTest, FieldTest){
	SmallGameShip ship;

	GameShip::FieldPtr field0;
	ship.setField(field0);


	GameShip::FieldPtr field(new Field(1));
	ship.setField(field);
	EXPECT_EQ(ship.getField(),field);

	SmallGameShip ship2(field0);
	EXPECT_EQ(ship2.getField(),nullptr);

	SmallGameShip ship3(field);
	EXPECT_EQ(ship3.getField(),field);
}

TEST_F(SmallGameShipTest, GameShipStateTest){

	SmallGameShip ship;

	GameShip::FieldPtr field0;

	GameShip::FieldPtr field(new Field(1));
	ship.setField(field);

	ship.changeState(field0, SmallGameShip::ShipState::HIT);
	EXPECT_EQ(ship.getState(), SmallGameShip::ShipState::FLOAT);

	ship.changeState(field, SmallGameShip::ShipState::HIT);
	EXPECT_EQ(ship.getState(), SmallGameShip::ShipState::HIT);
}


