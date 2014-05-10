/*
 * StatekTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "GameShip.h"

class GameShipTest : public ::testing::Test {
protected:
	GameShipTest() {};
	~GameShipTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(GameShipTest, ConstructorTest){
	GameShip ship;
}

TEST_F(GameShipTest, GameShipStateTest){
	GameShip ship;
	std::map<Field,GameShip::FactorState> ships;
	ship.setShipFactor(ships);
	EXPECT_EQ(ship.getSize(),0);

	Field field;
	field.setPoisiton(1);
	ship.changeState(field, GameShip::FactorState::HIT);
	EXPECT_EQ(ship.getState(), GameShip::ShipState::FLOAT);
}

TEST_F(GameShipTest, StatusTest){

}
