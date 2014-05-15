/*
 * gridcell.h
 *
 *  Created on: May 15, 2014
 *      Author: klis
 */

#ifndef GRIDCELL_H_
#define GRIDCELL_H_
#include <cstdlib>

class GridCell{
public:
	GridCell();
	GridCell(float red, float green, float blue,  int x, int y);

	void setColor(float red, float green, float blue); //add exception in arguments out of range
	void setCoordinates(int x, int y);

	int getX();
	int getY();

	float getRed();
	float getGreen();
	float getBlue();
private:
	float r_;
	float g_;
	float b_;

	int x_;
	int y_;
};



#endif /* GRIDCELL_H_ */
