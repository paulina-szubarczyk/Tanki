/*
 * BigShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "BigShip.h"
#include "SmallShip.h"
namespace game {
BigShip::BigShip() : IShip(){};

IShip::ShipState BigShip::getState() const {
	return state_;
}

std::size_t BigShip::getSize() const {
	return ships_.size();
}

void BigShip::addShip(ShipPtr ship){
	ships_.push_back(ship);
}

void BigShip::addShips(std::vector<ShipPtr> ships){
	ships_ = ships;
}

void BigShip::hit() {
	for (auto ship = ships_.begin(); ship != ships_.end(); ++ship){
		if ((*ship)->getState() == ShipState::FLOAT){
			state_ = ShipState::HIT;
			hitShip(state_);
			return;
		}
	}
	state_ = ShipState::SUNK;
	hitShip(state_);
}

void BigShip::registerShipObserver(ShipObserverPtr shipObserver){
	hitShip.connect(SignalShipType::slot_type( &ShipObserver::shipHit, shipObserver.get(), _1).track_foreign(shipObserver));
}

IShip* BigShip::createBigGameShip(int size){
	BigShip* ship = (new BigShip());
	for (int i = 0; i < size; ++i){
		ShipPtr smallShip(new SmallShip());
		ship->addShip(smallShip);
	}
	return ship;
}

std::vector<BigShip::ShipPtr> BigShip::getShips(){
	return ships_;
}
}
