/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "ShipFactoryMethod.h"
#include "SmallShip.h"
#include "BigShip.h"
using namespace game;
class ShipFactoryTest : public ::testing::Test {
protected:
	ShipFactoryTest() {};
	~ShipFactoryTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F( ShipFactoryTest, SingletonTest) {
	ShipFactoryMethod* shipFactory = ShipFactoryMethod::getInstance();
	EXPECT_FALSE(shipFactory == nullptr);
}

TEST_F( ShipFactoryTest, RegisterShipTest) {
	ShipFactoryMethod* shipFactory = ShipFactoryMethod::getInstance();
	shipFactory->registerShip("SmallShip",&SmallShip::createSmallGameShip);
	shipFactory->registerShip("BigShip",&BigShip::createBigGameShip);

	std::shared_ptr<SmallShip> smallShip(dynamic_cast<SmallShip*>(shipFactory->creatShip("SmallShip",1)));

	EXPECT_EQ(smallShip->getState(),IShip::ShipState::FLOAT);
	EXPECT_EQ(smallShip->getSize(),1);

	std::shared_ptr<BigShip> bigShip(dynamic_cast<BigShip*>(shipFactory->creatShip("BigShip", 0)));
	EXPECT_EQ(bigShip->getState(), IShip::ShipState::FLOAT);
	EXPECT_EQ(bigShip->getSize(),0);

	bigShip->addShip(smallShip);
	EXPECT_EQ(bigShip->getSize(),1);
}




