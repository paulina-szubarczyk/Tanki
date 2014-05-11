/*
 * BigGameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "BigGameShip.h"

BigGameShip::BigGameShip() : GameShip(GameShip::ShipState::FLOAT), HitObserver() {};
BigGameShip::~BigGameShip() {};
GameShip::ShipState BigGameShip::getState() const {
	return state_;
}

std::size_t BigGameShip::getSize() const {
	return ships_.size();
}

void BigGameShip::addShip(ShipPtr ship){
	ships_.push_back(ship);
}

void BigGameShip::addShips(std::vector<ShipPtr> ships){
	ships_ = ships;
}

void BigGameShip::hit() {
	for (auto ship = ships_.begin(); ship != ships_.end(); ++ship)
		if ((*ship)->getState() == GameShip::ShipState::FLOAT){
			state_ = GameShip::ShipState::HIT;
			return;
		}
	state_ = GameShip::ShipState::SUNK;
}
