/*
 * GameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "GameShip.h"
#include "Field.h"

GameShip::GameShip() : HitObserver() , state_(ShipState::FLOAT) {}
void GameShip::hit() {}


