/*
 * PlayerInput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#include "PlayerInput.h"
#include "GamePlayer.h"

#include "glog/logging.h"

#include <functional>

namespace plh = std::placeholders;

namespace ships {

PlayerInput::PlayerInput(MsgHandlerPtr msgHandler)
	: Input(msgHandler) {}

bool PlayerInput::registerAddShipMethod(PlayerPtr player, AddShipHandlerType handler) {

	return msgHandler_->addMsgHandler(MessageType::ADD_SHIP, std::bind(
			[](const MsgType& msg, PlayerPtr player, AddShipHandlerType handler) {

//		LOG(INFO) << "Received ADDS_SHIP";
//		ShipVec x;
//		ShipVec y;
//
//		for(int i = 0; i < msg.ships_size(); ++i) {
//			std::vector<int> xs;
//			std::vector<int> ys;
//			auto ship = msg.ships(i);
//			for(int j = 0; j < ship.x_size(); ++j) {
//				xs.push_back(ship.x(j));
//				ys.push_back(ship.y(j));
//			}
//			x.push_back(xs);
//			y.push_back(ys);
//		}
//
//		handler(player, y, x);
//		player->shipsAdded();

	}, plh::_1, player, handler));
}

void PlayerInput::setGamePlayer(PlayerPtr player) {

	msgHandler_->addMsgHandler(MessageType::HIT, std::bind(
			[](const MsgType& msg, PlayerPtr player) {

		LOG(INFO) << "Received HIT";
		player->hitField(msg.x(), msg.y());
	}, plh::_1, player));

	msgHandler_->addMsgHandler(MessageType::ADD_SHIP, std::bind(
			[](const MsgType& msg, PlayerPtr player) {

		LOG(INFO) << "Received ADD_SHIP";


		player->hitField(msg.x(), msg.y());
	}, plh::_1, player));


//	msgHandler_->addMsgHandler(MessageType::SURRENDER, std::bind(
//			[](const MsgType& msg, PlayerPtr player) {
//		LOG(INFO) << "Received SURRENDER";
//		player->surrender();
//	}, plh::_1, player));
}

} /* namespace ships */
