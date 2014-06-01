/*
 * gridcell.h
 *
 *  Created on: May 15, 2014
 *      Author: klis
 */

#ifndef GRIDCELL_H_
#define GRIDCELL_H_

class GridCell {
public:
	//Default constructor, sets cell's color to black and coordinates to 0
	GridCell();
	//Constructor, sets cell's color and coordinates
	GridCell(float red, float green, float blue, int x, int y);

	//Set color
	void setColor(float red, float green, float blue);
	//Set coordinates
	void setCoordinates(int x, int y);
	//Get coordinates
	int getX();
	int getY();
	//Get color
	float getRed();
	float getGreen();
	float getBlue();
	//Get/set "occupied" state
	bool getOccupied();
	void setOccupied(bool state);
	//Check if cell was already hit
	bool getHitState();
	//Set cell as a ship
	bool setToShip();

	bool hitCell();
	void registerHitReply(bool reply);

private:
	float r_;
	float g_;
	float b_;

	int x_;
	int y_;

	bool occupied_;
	bool alreadyHit_;
};

#endif /* GRIDCELL_H_ */
