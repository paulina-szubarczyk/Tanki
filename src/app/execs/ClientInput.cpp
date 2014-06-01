/*
 * ClientInput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: Adam Kosiorek
 */

#include "ClientInput.h"

#include "glog/logging.h"

#include <functional>
#include <map>

namespace plh = std::placeholders;

namespace ships {

ClientInput::ClientInput(ConnectionPtr connection, MsgHandlerPtr msgHandler)
	: Input(msgHandler)  {


	msgHandler_->addMsgHandler(MessageType::TURN, std::bind(
				[](const MsgType& msg, ConnectionPtr connection) {

			LOG(INFO) << "Received TURN";
			connection->setTurn(msg.turn());
		}, plh::_1, connection));

	msgHandler_->addMsgHandler(MessageType::HIT_REPLAY, std::bind(
				[](const MsgType& msg, ConnectionPtr connection) {

			LOG(INFO) << "Received HIT_REPLAY";
			connection->setHitReply(msg.x(), msg.y(), msg.this_());
		}, plh::_1, connection));

	msgHandler_->addMsgHandler(MessageType::CONFIG, std::bind(
				[](const MsgType& msg, ConnectionPtr connection) {

		LOG(INFO) << "Received CONFIG";
			connection->setGridSize(msg.grid_size());

			std::map<int, int> config;
			for(int i = 0; i < msg.ships_size(); ++i) {
				config[msg.ships(i).x(0)] = msg.ships(i).y(0);
			}

			connection->setShipsConfig(config);

		}, plh::_1, connection));
}


} /* namespace ships */
