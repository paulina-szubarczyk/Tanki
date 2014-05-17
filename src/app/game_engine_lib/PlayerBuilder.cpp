/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "PlayerBuilder.h"

PlayerBuilder::PlayerBuilder() {
<<<<<<< HEAD
	shipFactory = ShipFactoryMethod::getInstance();
	MsgSenderPtr msgSender = MsgSenderPtr(new ships::MessageSender(connection_));
	msgSender_ = msgSender;
=======

	shipFactory = ShipFactoryMethod::getInstance();
	shipFactory = ShipFactoryMethod::getInstance();
>>>>>>> It works great when tests are commented
}

PlayerBuilder::~PlayerBuilder() {
	// TODO Auto-generated destructor stub
}

