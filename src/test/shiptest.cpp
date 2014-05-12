/*
 * shiptest.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: klis
 */
#include "gtest/gtest.h"

#include "ship.h"
#include "test.pb.h"

class ShipTest : public ::testing::Test {
protected:
	ShipTest() {};
	~ShipTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(ShipTest, ConstructorTest){
	Ship s;
	ASSERT_EQ(s.getPointSize(), 50.0);

}

TEST_F(ShipTest, SetInstanceTest){
//	Ship s;
//	s.setInstance();
//	ASSERT_TRUE(s.getInstance());

}

TEST_F(ShipTest, AddCoordinatesTest){
//	Ship s;
//	s.addCoordinates(5,7);

//	ASSERT_TRUE(s.getVectorXSize());
//	ASSERT_TRUE(s.getVectorYSize());
//	ASSERT_EQ(s.getX(0), 5);
//	ASSERT_EQ(s.getY(0), 7);
//	ASSERT_EQ(1,0);
}

TEST_F(ShipTest, EraseTest){
//	Ship s;
//	for(int j = 0; j < 100; j++){
//		s.addCoordinates(1,1);
//	}
//	ASSERT_TRUE(s.getVectorXSize());
//	ASSERT_TRUE(s.getVectorYSize());
//
//	s.clear();
//	ASSERT_FALSE(s.getVectorXSize());
//	ASSERT_FALSE(s.getVectorYSize());

}




