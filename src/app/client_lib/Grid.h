/*
 * Grid.h
 *
 *  Created on: May 16, 2014
 *      Author: klis
 */

#ifndef GRID_H_
#define GRID_H_

#include "GridCell.h"
#include <vector>
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<GridCell> CellPtr;
class Grid{
public:
	Grid();
	Grid(int n);
	//~Grid();



	void init();
	void addNewCell();
	void addNewShip();

	CellPtr getCell();
	int getGridSize();
	const std::vector<CellPtr>& getGrid();

private:
std::vector<CellPtr> grid_;
};


#endif /* GRID_H_ */
