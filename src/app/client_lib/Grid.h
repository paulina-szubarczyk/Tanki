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
#include <memory>
#include "boost/multi_array.hpp"
#include <vector>

typedef std::shared_ptr<GridCell> CellPtr;
typedef boost::multi_array<CellPtr, 2> array2D;
class Grid {
public:
	Grid();
	Grid(int n);

	void init(int n);
	std::vector<std::pair<int, int> > addNewShip(int x, int y, int size,
			int horizontal);
	bool checkAddSize(int x, int y, int size, int horizontal);
	bool checkAvaible(int x, int y, int size, int horizontal);

	std::vector<std::vector<std::pair<int, int> > >& getShips(){return ships_;}
	int getGridSize();
	const array2D& getGrid();

private:
	std::vector<std::vector<std::pair<int, int> > > ships_;
	array2D grid_;

};

#endif /* GRID_H_ */
