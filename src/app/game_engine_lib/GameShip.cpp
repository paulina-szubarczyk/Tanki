/*
 * GameShip.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#include "GameShip.h"
#include <exception>
#include <iostream>

GameShip::GameShip() {
	state_ = ShipState::FLOAT;
}

GameShip::~GameShip() {
	// TODO Auto-generated destructor stub
}


void GameShip::changeState(Field* field, ShipState state){
	state_ = state;
}

void GameShip::updateState(){}
