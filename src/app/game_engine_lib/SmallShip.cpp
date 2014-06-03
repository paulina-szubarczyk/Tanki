/*
 * SmallShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "SmallShip.h"
#include "Field.h"
namespace game {
SmallShip::SmallShip() : IShip() {}


IShip::ShipState SmallShip::getState() const {
	return state_;
}

std::size_t  SmallShip::getSize() const {
	return 1;
}

void SmallShip::hit() {
	state_ = IShip::ShipState::SUNK;
}

IShip* SmallShip::createSmallGameShip(int) {
	return (new SmallShip());
}
}
