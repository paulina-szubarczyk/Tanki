/*
 * SmallGameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "SmallGameShip.h"
#include "Field.h"
#include <iostream>

SmallGameShip::SmallGameShip() : GameShip(GameShip::ShipState::FLOAT) {}


GameShip::ShipState SmallGameShip::getState() const {
	return state_;
}

std::size_t  SmallGameShip::getSize() const {
	return 1;
}

void SmallGameShip::hit() {
	state_ = GameShip::ShipState::SUNK;
}

std::shared_ptr<SmallGameShip> SmallGameShip::createSmallGameShip(int) {
	return std::shared_ptr<SmallGameShip>(new SmallGameShip());
}
