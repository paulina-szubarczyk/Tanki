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
	std::shared_ptr<Grid> grid (new Grid(n));
	ASSERT_EQ(grid->getGridSize(), n );

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			ASSERT_EQ(grid->getGrid()[i][j]->getX(), i);
			ASSERT_EQ(grid->getGrid()[i][j]->getY(), j);
		}
}

TEST_F(GridTest, GridManipulationTest) {

	std::shared_ptr<Grid> grid (new Grid);
	ASSERT_EQ(grid->getGridSize(), 0);
	grid->init(5);
	ASSERT_EQ(grid->getGridSize(), 5);

	grid->getGrid()[0][0]->setColor(0.2, 0.3, 0.4);
	ASSERT_FLOAT_EQ(grid->getGrid()[0][0]->getRed(), 0.2);
	ASSERT_FLOAT_EQ(grid->getGrid()[0][0]->getGreen(), 0.3);
	ASSERT_FLOAT_EQ(grid->getGrid()[0][0]->getBlue(), 0.4);


}

TEST_F(GridTest, AddShipTest){
	std::shared_ptr<Grid> grid (new Grid(10));
	grid->addNewShip(1,1,5,0);

	for(int i=1; i< 6; ++i)
		ASSERT_TRUE(grid->getGrid()[i][1]->getOccupied());
	ASSERT_FALSE(grid->getGrid()[0][1]->getOccupied());
	ASSERT_FALSE(grid->getGrid()[6][1]->getOccupied());

	grid->addNewShip(1,3,5,1);
	for(int j=3; j< 8; ++j)
			ASSERT_TRUE(grid->getGrid()[1][j]->getOccupied());
		ASSERT_FALSE(grid->getGrid()[1][2]->getOccupied());
		ASSERT_FALSE(grid->getGrid()[1][8]->getOccupied());

}

TEST_F(GridTest, CheckAddSizeTest){

	std::shared_ptr<Grid> grid (new Grid(10));

	for(int i = 0; i<10;++i)
		for(int j = 0; j<10;j++)
	ASSERT_TRUE(grid->checkAddSize(i,j,1,0));

	for(int i = 0; i<9;++i)
			for(int j = 0; j<10;j++){
				ASSERT_TRUE(grid->checkAddSize(i,j,2,0));
				ASSERT_FALSE(grid->checkAddSize(9,j,2,0));
			}
	for(int i = 0; i<10;++i)
			for(int j = 0; j<9;j++){
				ASSERT_TRUE(grid->checkAddSize(i,j,2,1));
				ASSERT_FALSE(grid->checkAddSize(i,9,2,1));
			}
}


TEST_F(GridTest, CheckAvaibleTest){

	std::shared_ptr<Grid> grid (new Grid(10));
	grid->addNewShip(3,3,3,0);

	for(int i = 2; i<6;++i)
		for(int j = 2; j<4;j++)
	ASSERT_FALSE(grid->checkAvaible(3,2,2,0));

	for(int i = 2; i<6;++i)
			for(int j = 2; j<4;j++)
		ASSERT_FALSE(grid->checkAvaible(3,2,2,1));
}
