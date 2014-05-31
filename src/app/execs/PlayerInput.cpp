/*
 * PlayerInput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#include "PlayerInput.h"

#include <functional>

namespace plh = std::placeholders;

namespace ships {

PlayerInput::PlayerInput(MsgHandlerPtr msgHandler)
	: Input(msgHandler) {}

bool PlayerInput::registerAddShipMethod(HandlerType handler) {

	return msgHandler_->addMsgHandler(MessageType::ADD_SHIP, handler);
}

void PlayerInput::setGamePlayer(PlayerPtr player) {

	msgHandler_->addMsgHandler(MessageType::HIT, std::bind(
			[](const MsgType& msg, PlayerPtr player) {
		player->hitField(msg.x(), msg.y());
	}, plh::_1, player));


//	msgHandler_->addMsgHandler(MessageType::SURRENDER, std::bind(
//			[](const MsgType& msg, PlayerPtr player) {
//		player->surrender();
//	}, plh::_1, player));
}

} /* namespace ships */
