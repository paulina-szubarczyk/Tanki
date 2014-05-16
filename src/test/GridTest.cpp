/*
 * GridTest.cpp
 *
 *  Created on: May 16, 2014
 *      Author: klis
 */


#include "gtest/gtest.h"
#include "Grid.h"

class GridTest : public ::testing::Test {
protected:
	GridTest() {};
	~GridTest() {};
	virtual void SetUp() {};
	virtual void TeatDown() {};
};

TEST_F(GridTest, InitializationTest){

	Grid grid(10);
	ASSERT_EQ(grid.getGridSize(),100);

	int i = 0;
	int k = 0;
	for(auto cell : grid.getGrid()){
		k = (cell->getX() + cell->getY()*10);
		ASSERT_EQ(i,k);
		++i;
	}
}
