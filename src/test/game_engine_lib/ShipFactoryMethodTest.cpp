/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "ShipFactoryMethod.h"
#include "SmallGameShip.h"
#include "BigGameShip.h"

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
	shipFactory->registerShip("SmallShip",&SmallGameShip::createSmallGameShip);
	shipFactory->registerShip("BigShip",&BigGameShip::createBigGameShip);

	std::shared_ptr<SmallGameShip> smallShip(dynamic_cast<SmallGameShip*>(shipFactory->creatShip("SmallShip",1)));

	EXPECT_EQ(smallShip->getState(),GameShip::ShipState::FLOAT);
	EXPECT_EQ(smallShip->getSize(),1);

	std::shared_ptr<BigGameShip> bigShip(dynamic_cast<BigGameShip*>(shipFactory->creatShip("BigShip", 0)));
	EXPECT_EQ(bigShip->getState(), GameShip::ShipState::FLOAT);
	EXPECT_EQ(bigShip->getSize(),0);

	bigShip->addShip(smallShip);
	EXPECT_EQ(bigShip->getSize(),1);
}




