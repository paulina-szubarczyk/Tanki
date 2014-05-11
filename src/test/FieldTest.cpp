/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "Field.h"
#include "SmallGameShip.h"

class FieldTest : public ::testing::Test {
protected:
	FieldTest() {};
	~FieldTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(FieldTest, ConstructorTest){
	Field field;
}

TEST_F(FieldTest, PositionTest){
	Field field;
	EXPECT_EQ(field.getPosition(),0);
}

TEST_F(FieldTest, OperatorLessThenTest){
	Field field1(10), field2(1);
	EXPECT_TRUE(field2<field1);
}

TEST_F(FieldTest, ShipOnFieldTest){
	std::shared_ptr<Field> field_ptr(new Field(1));
//	std::shared_ptr<SmallGameShip> ship_ptr(new SmallGameShip());
//	field_ptr->setShip(ship_ptr);
//	EXPECT_TRUE(field_ptr->getShip().lock()==ship_ptr);
}



