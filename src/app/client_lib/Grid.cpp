/*
 * Grid.cpp
 *
 *  Created on: May 16, 2014
 *      Author: klis
 */

#include "Grid.h"

Grid::Grid(){

}

Grid::Grid(int n){
	init(n);
}
void Grid::init(int n){
	grid_.resize(boost::extents[n][n]);
	for(int i = 0; i < n; i++)
		for(int j=0; j<n; j++){
			//addNewCell(grid_[i][j]);
			grid_[i][j].reset(new GridCell);
			grid_[i][j]->setCoordinates(i,j);
		}

}

void Grid::gridResize(int n){
	//grid_.resize(boost::extents[n][n]);
	init(n);
}

void Grid::addNewShip(){

}

CellPtr Grid::getCell(){
	return CellPtr (nullptr);
}
int Grid::getGridSize(){
	return grid_.num_elements();
}

const array2D& Grid::getGrid(){
	return grid_;
}
