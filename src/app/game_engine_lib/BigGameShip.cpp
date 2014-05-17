/*
 * BigGameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "BigGameShip.h"
#include "SmallGameShip.h"

BigGameShip::BigGameShip() : GameShip(){};

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
	for (auto ship = ships_.begin(); ship != ships_.end(); ++ship){
		if ((*ship)->getState() == ShipState::FLOAT){
			state_ = ShipState::HIT;
			return;
		}
	}
	state_ = ShipState::SUNK;
}

void BigGameShip::registerShipObserver(ShipObserverPtr shipObserver){
	hitShip.connect(SignalShipType::slot_type( &ShipObserver::shipHit, shipObserver.get()).track_foreign(shipObserver));
}

GameShip* BigGameShip::createBigGameShip(int size){
	BigGameShip* ship = (new BigGameShip());
	for (int i = 0; i < size; ++i){
		ShipPtr smallShip(new SmallGameShip());
		ship->addShip(smallShip);
	}
	return ship;
}

std::vector<BigGameShip::ShipPtr> BigGameShip::getShips(){
	return ships_;
}
