/*
 * FieldTest.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */
#include "gtest/gtest.h"
#include "Field.h"

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
	field.setPoisiton(10);
	EXPECT_EQ(field.getPosition(),10);
}

TEST_F(FieldTest, OperatorLessThenTest){
	Field field1, field2;
	field1.setPoisiton(10);
	field2.setPoisiton(1);
	EXPECT_TRUE(field2<field1);
}



