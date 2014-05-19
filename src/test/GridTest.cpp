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

TEST_F(GridTest, InitializationTest) {

	int n = 10;
	Grid grid(n);
	ASSERT_EQ(grid.getGridSize(), n * n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			ASSERT_EQ(grid.getGrid()[i][j]->getX(), i);
			ASSERT_EQ(grid.getGrid()[i][j]->getY(), j);
		}
}

TEST_F(GridTest, GridManipulationTest) {
	Grid grid;
	ASSERT_EQ(grid.getGridSize(), 0);
	grid.init(5);
	ASSERT_EQ(grid.getGridSize(), 25);

	grid.getGrid()[0][0]->setColor(0.2, 0.3, 0.4);
	ASSERT_FLOAT_EQ(grid.getGrid()[0][0]->getRed(), 0.2);
	ASSERT_FLOAT_EQ(grid.getGrid()[0][0]->getGreen(), 0.3);
	ASSERT_FLOAT_EQ(grid.getGrid()[0][0]->getBlue(), 0.4);

	CellPtr ship(new GridCell(0.1, 0.2, 0.3, 2, 4));
	grid.addNewShip(ship);

}
