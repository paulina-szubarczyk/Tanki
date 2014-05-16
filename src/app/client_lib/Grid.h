/*
 * Grid.h
 *
 *  Created on: May 16, 2014
 *      Author: klis
 */

#ifndef GRID_H_
#define GRID_H_

#include "GridCell.h"
//#include <vector>
#include <boost/shared_ptr.hpp>
#include "boost/multi_array.hpp"

typedef boost::shared_ptr<GridCell> CellPtr;
typedef boost::multi_array<CellPtr, 2> array2D;
class Grid{
public:
	Grid();
	Grid(int n);
	//~Grid();


	typedef array2D::index index;


	void init(int n);
	void addNewCell(CellPtr ptr);
	void addNewShip();

	CellPtr getCell();
	int getGridSize();
	const array2D& getGrid();

private:
//std::vector<CellPtr> grid_;
array2D grid_;

};


#endif /* GRID_H_ */
