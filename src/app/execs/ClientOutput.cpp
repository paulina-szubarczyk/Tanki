/*
 * ClientOutput.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: Adam Kosiorek
 */

#include "ClientOutput.h"

namespace ships {


ClientOutput::ClientOutput(ConnectionPtr connection)
	:connection_(connection) {}

void ClientOutput::connect(std::string serverIP, unsigned short port) {
	connection_->connect(serverIP, port);
}

void ClientOutput::sendShip(std::vector<std::vector<std::pair<int, int>>> shipVec) {

	auto msg = createMsg(MessageType::ADD_SHIP);

	for(const auto& ship : shipVec) {
		auto newShip = msg->add_ships();
		for(const auto& segment : ship) {
			newShip->add_x(segment.first);
			newShip->add_y(segment.second);
		}
	}
}

void ClientOutput::sendHit(std::pair<int, int> hitCoordinates) {

	auto msg = createMsg(MessageType::HIT);
	msg->set_x(hitCoordinates.first);
	msg->set_y(hitCoordinates.second);
	send(msg);
}

auto ClientOutput::createMsg(MessageType type) const -> MsgPtr {
	auto msg = std::make_shared<DataMsg>();
	msg->set_type(type);
	return msg;
}

void ClientOutput::send(MsgPtr msg) const {
	connection_->send(msg);
}

} /* namespace ships */
