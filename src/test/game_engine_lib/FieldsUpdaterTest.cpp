/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "FieldsUpdater.h"
#include "GamePlayer.h"
#include "ProtobufConnection.h"
#include <boost/signals2/signal.hpp>
#include "array"
using namespace game;
class FieldsUpdaterTest : public ::testing::Test {
protected:
	FieldsUpdaterTest() {};
	~FieldsUpdaterTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(FieldsUpdaterTest, ConstructorTest){
//	PlayerOutput output()
//	FieldsUpdater field()
}

TEST_F(FieldsUpdaterTest, HitTest){

//	std::shared_ptr<Gameboard> gameboard(new Gameboard(5));
//	std::shared_ptr<FieldsUpdater> fieldsUpd(new FieldsUpdater(gameboard));
//	std::pair<int,int> pole = std::make_pair(1,2);
//	std::pair<int,int>  pole1;
//
//
//	fieldsUpd->hit(1,2);
//	EXPECT_TRUE(fieldsUpd->getLastHit() == pole);
//	EXPECT_FALSE(fieldsUpd->getLastHit() == pole1);
}

TEST_F(FieldsUpdaterTest, ShipHitTest){
}

TEST_F(FieldsUpdaterTest, GetLastHitTest){
}

TEST_F(FieldsUpdaterTest, ShipsNotHitTest){
}
