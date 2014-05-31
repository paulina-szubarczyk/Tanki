/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "PlayerBuilder.h"

PlayerBuilder::PlayerBuilder() {
	shipFactory = ShipFactoryMethod::getInstance();
	//MsgSenderPtr msgSender = MsgSenderPtr(new ships::MessageSender(connection_));
	//msgSender_ = msgSender;

}

PlayerBuilder::~PlayerBuilder() {
	// TODO Auto-generated destructor stub
}

