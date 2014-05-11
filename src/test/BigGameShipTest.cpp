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
	class TestUnitShip : public GameShip {
	public:
		TestUnitShip() : GameShip() {} ;
		virtual GameShip::ShipState getState() const { return state_;}
		virtual void hit() {
//			std::cout << "I'm hitten\n";
			state_ = GameShip::ShipState::SUNK; }
	};
	typedef std::shared_ptr<GameShip> TestShipPtr;
};
TEST_F(BigGameShipTest, ConstructorTest){
	BigGameShip ship;
	EXPECT_EQ(ship.getState(), GameShip::ShipState::FLOAT);
	EXPECT_EQ(ship.getSize(),0);
}

TEST_F(BigGameShipTest, AddShipsTest){

	std::vector<TestShipPtr> ships;
	for (int i=0; i<4; ++i)
		ships.push_back(TestShipPtr(new TestUnitShip()));

	BigGameShip bigship;
	bigship.addShips(ships);
	EXPECT_EQ(bigship.getSize(),4);
}

TEST_F(BigGameShipTest, AddShipTest){

	std::vector<TestShipPtr> ships;
	for (int i=0; i<4; ++i)
		ships.push_back(TestShipPtr(new TestUnitShip()));

	BigGameShip bigship1;
	for (int i=0; i<4; ++i){
		bigship1.addShip(ships[i]);
	}
	EXPECT_EQ(bigship1.getSize(),4);
}
TEST_F(BigGameShipTest, GameShipStateTest){

	std::vector<TestShipPtr> ships;
	for (int i=0; i<4; ++i)
		ships.push_back(TestShipPtr(new TestUnitShip()));

	BigGameShip bigship;
	bigship.addShips(ships);

	EXPECT_TRUE(bigship.getState() == GameShip::ShipState::FLOAT);

	for (int i=0; i<3; ++i){
		ships[i]->hit();
		bigship.hit();
		EXPECT_TRUE(bigship.getState() == GameShip::ShipState::HIT);
	}
	ships[3]->hit();
	bigship.hit();
	EXPECT_TRUE(bigship.getState() == GameShip::ShipState::SUNK);
}


