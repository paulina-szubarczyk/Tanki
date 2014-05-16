/*
 * Grid.cpp
 *
 *  Created on: May 16, 2014
 *      Author: klis
 */

#include "Grid.h"

Grid::Grid(){
	init();
}

Grid::Grid(int n){
	init();
}
void Grid::init(){

}

void Grid::addNewCell(){
	CellPtr newCell(new GridCell);
	grid_.push_back(newCell);
}

void Grid::addNewShip(){

}

CellPtr Grid::getCell(){
	return CellPtr (nullptr);
}
int Grid::getGridSize(){
	return grid_.size();
}

const std::vector<CellPtr>& Grid::getGrid(){
	return grid_;
}
