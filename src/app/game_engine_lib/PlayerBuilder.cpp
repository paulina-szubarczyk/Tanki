/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "PlayerBuilder.h"

#include "glog/logging.h"

PlayerBuilder::PlayerBuilder()
	: shipFactory(ShipFactoryMethod::getInstance()) {}


void PlayerBuilder::createPlayer(OutputPtr output) {

	LOG(INFO) << "Creating a player";
	player_ = new GamePlayer(output);
}
