/*
 * Field.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#include "Field.h"
#include "SmallGameShip.h"

Field::Field():position_(0) {}
Field::Field(int position):position_(position) {}
Field::~Field() {}

int Field::getPosition() const  {
	return position_;
}

void Field::setShip(ShipPtr ship){
	ship_ = ship;
}

Field::ShipPtr Field::getShip(){
	return ship_;
}
