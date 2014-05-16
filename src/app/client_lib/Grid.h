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
class Grid{
public:
	Grid();
	~Grid();

	typedef boost::shared_ptr<GridCell> CellPtr;

	void init();
	void addNewCell();
	void addNewShip();

	CellPtr getCell();
	int getGridSize();
	boost::shared_ptr<std::vector<CellPtr>> getGrid();

private:
std::vector<CellPtr> grid_;
};


#endif /* GRID_H_ */
