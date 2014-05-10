/*
 * GameShipAggregator.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "GameShipAggregator.h"

GameShipAggregator::GameShipAggregator() {
	// TODO Auto-generated constructor stub

}

GameShipAggregator::~GameShipAggregator() {
	// TODO Auto-generated destructor stub
}

void GameShipAggregator::setGameShips(std::map<Field,GameShip> ships) {
	ships_ = ships;
}

size_t GameShipAggregator::getSize(){
	return ships_.size();
}

void GameShipAggregator::changeState(Field field, ShipState state){
	try{
		ships_.at(field) = state;
		this->updateState();
	}
	catch(std::exception &e){
		std::cerr << "Field on position "<< field.getPosition() << " not found\n";
	}
}

void GameShipAggregator::updateState(){
	for (auto it = ships_.begin(); it!=ships_.end(); ++it )
		if (it->second == AbstractShip::ShipState::FLOAT)
			return;
	state_ = AbstractShip::ShipState::SUNK;
}
