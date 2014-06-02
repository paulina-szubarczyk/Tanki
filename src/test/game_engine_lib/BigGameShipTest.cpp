///*
// * StatekTest.cpp
// *
// *  Created on: May 10, 2014
// *      Author: paulina
// */
#include "gtest/gtest.h"
#include "BigShip.h"
#include "SmallShip.h"
#include <iostream>
using namespace game;

class BigGameShipTest : public ::testing::Test {
protected:
	BigGameShipTest() {};
	~BigGameShipTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};

	class TestUnitShip : public IShip {
	public:
		TestUnitShip() = default;

		virtual std::size_t getSize() const {};
		virtual void addShip(ShipPtr ship) {};
		virtual void addShips(std::vector<ShipPtr> ships) {};

		virtual ShipState getState() const { return state_;}
		virtual void hit() {
			state_ = IShip::ShipState::SUNK; }
	};

	typedef std::shared_ptr<IShip> TestShipPtr;
};
TEST_F(BigGameShipTest, ConstructorTest){
	BigShip ship;
	EXPECT_EQ(ship.getState(), IShip::ShipState::FLOAT);
	EXPECT_EQ(ship.getSize(),0);
}

TEST_F(BigGameShipTest, AddShipsTest){

	std::vector<TestShipPtr> ships;
	for (int i=0; i<4; ++i)
		ships.push_back(TestShipPtr(new TestUnitShip()));

	BigShip bigship;
	bigship.addShips(ships);
	EXPECT_EQ(bigship.getSize(),4);
}

TEST_F(BigGameShipTest, AddShipTest){

	std::vector<TestShipPtr> ships;
	for (int i=0; i<4; ++i)
		ships.push_back(TestShipPtr(new TestUnitShip()));

	BigShip bigship1;
	for (int i=0; i<4; ++i){
		bigship1.addShip(ships[i]);
	}
	EXPECT_EQ(bigship1.getSize(),4);
}
TEST_F(BigGameShipTest, GameShipStateAndHitTest){

	std::vector<TestShipPtr> ships;
	for (int i=0; i<4; ++i)
		ships.push_back(TestShipPtr(new TestUnitShip()));

	BigShip bigship;
	bigship.addShips(ships);

	EXPECT_TRUE(bigship.getState() == IShip::ShipState::FLOAT);

	for (int i=0; i<3; ++i){
		ships[i]->hit();
		bigship.hit();
		EXPECT_TRUE(bigship.getState() == IShip::ShipState::HIT);
	}
	ships[3]->hit();
	bigship.hit();
	EXPECT_TRUE(bigship.getState() == IShip::ShipState::SUNK);
}
TEST_F(BigGameShipTest, RegisterShipObserverTest){
	std::shared_ptr<BigShip> ship(new BigShip());

	class TestShipObserver : public ShipObserver{
	public:
		TestShipObserver() : ShipObserver(), id_(0), state_(0) {};
		TestShipObserver(int id) : ShipObserver(), id_(id), state_(0) {};
		~TestShipObserver() = default;
		void shipHit(IShip::ShipState state) {
			++state_ ;
		}
		int getState() {return state_; }
	private:
		int id_;
		int state_;
	};

	std::shared_ptr<TestShipObserver> tsobs(new TestShipObserver());
	ship->registerShipObserver(tsobs);
	EXPECT_EQ(tsobs->getState(), 0);
	ship->hitShip(IShip::ShipState::HIT);
	EXPECT_EQ(tsobs->getState(), 1);

	std::shared_ptr<TestShipObserver> tsobs2(new TestShipObserver(1));
	ship->registerShipObserver(tsobs2);
	EXPECT_EQ(tsobs2->getState(), 0);
	EXPECT_EQ(tsobs->getState(), 1);
	ship->hitShip(IShip::ShipState::SUNK);
	EXPECT_EQ(tsobs->getState(), 2);
	EXPECT_EQ(tsobs2->getState(), 1);
}

TEST_F(BigGameShipTest, CreateShipTest){

	std::shared_ptr<BigShip> bigship(dynamic_cast<BigShip*>(BigShip::createBigGameShip(4)));
	EXPECT_EQ(bigship->getSize(),4);
}


