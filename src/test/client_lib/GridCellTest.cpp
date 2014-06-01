/*
 * GridCellTest.cpp
 *
 *  Created on: May 15, 2014
 *      Author: klis
 */

#include "gtest/gtest.h"
#include "GridCell.h"

class GridCellTest : public ::testing::Test {
protected:
	GridCellTest() {};
	~GridCellTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(GridCellTest,ConstructorTest){

	GridCell cell;
	ASSERT_FLOAT_EQ(cell.getRed(), 0.0);
	ASSERT_FLOAT_EQ(cell.getGreen(), 0.0);
	ASSERT_FLOAT_EQ(cell.getBlue(), 0.0);
	ASSERT_EQ(cell.getX(), 0);
	ASSERT_EQ(cell.getY(), 0);
	ASSERT_FALSE(cell.getOccupied());

	cell.setOccupied(true);
	ASSERT_TRUE(cell.getOccupied());

	GridCell c2(0.4, 0.2, 0.1, 5, 8);
	ASSERT_FLOAT_EQ(c2.getRed(), 0.4);
	ASSERT_FLOAT_EQ(c2.getGreen(), 0.2);
	ASSERT_FLOAT_EQ(c2.getBlue(), 0.1);
	ASSERT_EQ(c2.getX(), 5);
	ASSERT_EQ(c2.getY(), 8);
}

TEST_F(GridCellTest,SetColorTest){
	GridCell cell;
	cell.setColor(0.2, 0.4, 0.9);
	ASSERT_FLOAT_EQ(cell.getRed(), 0.2);
	ASSERT_FLOAT_EQ(cell.getGreen(), 0.4);
	ASSERT_FLOAT_EQ(cell.getBlue(), 0.9);
}

TEST_F(GridCellTest,SetColorOverRangeTest){
	GridCell cell;
	cell.setColor(1.2, -5.4, 10.9);
	ASSERT_FLOAT_EQ(cell.getRed(), 1.0);
	ASSERT_FLOAT_EQ(cell.getGreen(), 0.);
	ASSERT_FLOAT_EQ(cell.getBlue(), 1.0);
}

TEST_F(GridCellTest,SetCoordinatesTest){
	GridCell cell;
	cell.setCoordinates(7, 55);
	ASSERT_EQ(cell.getX(), 7);
	ASSERT_EQ(cell.getY(), 55);
}

TEST_F(GridCellTest, SetShipTest){
	GridCell cell;
	ASSERT_TRUE(cell.setToShip());
	ASSERT_TRUE(cell.getOccupied());
	ASSERT_FLOAT_EQ(cell.getRed(), 0.0);
	ASSERT_FLOAT_EQ(cell.getGreen(),1.0 );
	ASSERT_FLOAT_EQ(cell.getBlue(), 0.0);
	ASSERT_FALSE(cell.setToShip());

}

TEST_F(GridCellTest, HitCellTest){
	GridCell cell;
	ASSERT_FALSE(cell.hitCell());
	GridCell cell2;
	cell2.setToShip();
	ASSERT_TRUE(cell2.hitCell());
	ASSERT_FLOAT_EQ(cell2.getRed(), 1.0);
	ASSERT_FLOAT_EQ(cell2.getGreen(),0.0 );
	ASSERT_FLOAT_EQ(cell2.getBlue(), 0.0);
	ASSERT_TRUE(cell2.getHitState());
	ASSERT_FALSE(cell.hitCell());

}

TEST_F(GridCellTest, RegisterReplyTest){

	GridCell cell;
	ASSERT_FALSE(cell.getHitState());
	cell.registerHitReply(false);
	ASSERT_TRUE(cell.getHitState());


}
