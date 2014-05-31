/*
 * Grid.cpp
 *
 *  Created on: May 16, 2014
 *      Author: klis
 */

#include "Grid.h"

Grid::Grid() {

}

Grid::Grid(int n) {
	init(n);
}
void Grid::init(int n) {
	grid_.resize(boost::extents[n][n]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			grid_[i][j].reset(new GridCell(0.0, 0.0, 0.7, i, j));
			grid_[i][j]->setCoordinates(i, j);
		}

}

bool Grid::checkAddSize(int x, int y, int size, int horizontal) {
	if (horizontal == 0) {
		if (x + size - 1 < getGridSize())
			return true;
	} else {
		if (y + size - 1 < getGridSize())
			return true;
	}
	return false;

}
bool Grid::checkAvaible(int x, int y, int size, int horizontal) {
	int tmpi = x;
	int tmpj = y;
	int endX = (x + size) < getGridSize() ? (x + size + 1) : getGridSize();
	int endY = (y + size) < getGridSize() ? (y + size + 1) : getGridSize();
	if (x > 0)
		tmpi = x - 1;
	if (y > 0)
		tmpj = y - 1;
	if (horizontal == 0) {
		int tempY = (y + 2) < getGridSize() ? (y + 2) : getGridSize();

		for (int i = tmpi; i < endX; i++) {
			for (int j = tmpj; j < tempY; j++) {
				if (grid_[i][j]->getOccupied())
					return false;
			}
		}
	} else {
		int tempX = (x + 2) < getGridSize() ? (x + 2) : getGridSize();
		for (int j = tmpj; j < endY; ++j)
			for (int i = tmpi; i < tempX; ++i)
				if (grid_[i][j]->getOccupied())
					return false;
	}
	return true;
}

std::vector<std::pair<int, int> > Grid::addNewShip(int x, int y, int size,
		int horizontal) {
	//checkAddSize(x,y,size,horizontal);
	std::vector < std::pair<int, int> > ship;
	if (horizontal == 0) {
		for (int i = 0; i < size; i++) {
			ship.push_back(std::pair<int, int>(x, y));
			grid_[x++][y]->setToShip();
		}
	} else {
		for (int i = 0; i < size; i++) {
			ship.push_back(std::pair<int, int>(x, y));
			grid_[x][y++]->setToShip();
		}
	}
	return ship;
}

void Grid::addBigShipHorizontal(CellPtr bigship) {

}

void Grid::addBigShipVertical(CellPtr bigship) {

}
CellPtr Grid::getCell() {
	return CellPtr(nullptr);
}
int Grid::getGridSize() {
	return grid_.size();
}

const array2D& Grid::getGrid() {
	return grid_;
}
