/*
 * SmallGameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "SmallGameShip.h"
#include "Field.h"

SmallGameShip::SmallGameShip() : GameShip() {}


GameShip::ShipState SmallGameShip::getState() const {
	return state_;
}

std::size_t  SmallGameShip::getSize() const {
	return 1;
}

void SmallGameShip::hit() {
	state_ = GameShip::ShipState::SUNK;
}

GameShip* SmallGameShip::createSmallGameShip(int) {
	return (new SmallGameShip());
}
