/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "PlayerBuilder.h"

PlayerBuilder::PlayerBuilder() {
	 shipFactory = ShipFactoryMethod::getInstance();
}

PlayerBuilder::~PlayerBuilder() {
	// TODO Auto-generated destructor stub
}

