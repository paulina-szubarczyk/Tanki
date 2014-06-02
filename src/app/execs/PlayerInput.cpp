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
#include <stdexcept>

namespace plh = std::placeholders;

PlayerInput::PlayerInput(MsgHandlerPtr msgHandler)
	: Input(msgHandler) {}

void PlayerInput::registerAddShipMethod(AddShipHandlerType handler) {

	if(!player_) {

		std::logic_error err("Cannot bind handler to a null player. Set player first");
		LOG(ERROR) << err.what();
		throw err;
	}

	if(!msgHandler_->addMsgHandler(MessageType::ADD_SHIP, std::bind(
			[](const MsgType& msg, PlayerPtr player_, AddShipHandlerType handler) {

		LOG(INFO) << "Received ADD_SHIP";
		ShipVec x;
		ShipVec y;

		for(int i = 0; i < msg.ships_size(); ++i) {
			std::vector<int> xs;
			std::vector<int> ys;
			auto ship = msg.ships(i);
			for(int j = 0; j < ship.x_size(); ++j) {
				xs.push_back(ship.x(j));
				ys.push_back(ship.y(j));
			}
			x.push_back(xs);
			y.push_back(ys);
		}

		handler(player_, y, x);
		player_->shipsAdded();

	}, plh::_1, player_, handler))) {

		std::runtime_error err("Couldn't add AddShipHandler");
		LOG(ERROR) << err.what();
		throw err;
	}
}

void PlayerInput::setGamePlayer(PlayerPtr player) {

	if(!player) {
		std::invalid_argument err("Cannot bind input to a null player");
		LOG(ERROR) << err.what();
		throw err;
	}

	player_ = player;
	msgHandler_->addMsgHandler(MessageType::HIT, std::bind(
			[](const MsgType& msg, PlayerPtr player_) {

		LOG(INFO) << "Received HIT";
		player_->hitField(msg.x(), msg.y());
	}, plh::_1, player_));



//	msgHandler_->addMsgHandler(MessageType::SURRENDER, std::bind(
//			[](const MsgType& msg, PlayerPtr player) {
//		LOG(INFO) << "Received SURRENDER";
//		player->surrender();
//	}, plh::_1, player));
}
