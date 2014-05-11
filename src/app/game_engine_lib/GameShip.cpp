/*
 * GameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "GameShip.h"
#include "Field.h"

GameShip::GameShip() : state_(ShipState::FLOAT) {}
GameShip::GameShip(ShipState state) : state_(state){}


