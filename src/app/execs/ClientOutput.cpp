/*
 * ClientOutput.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: Adam Kosiorek
 */

#include "ClientOutput.h"

#include "glog/logging.h"

using namespace net;

ClientOutput::ClientOutput(ConnectionPtr connection)
	: IOutput(connection) {}

void ClientOutput::connect(std::string serverIP, unsigned short port) {
	LOG(INFO) << "Connecting";
	connection_->connect(serverIP, port);
}

void ClientOutput::sendShip(std::vector<std::vector<std::pair<int, int>>> shipVec) {

	LOG(INFO) << "Sending ADD_SHIP";
	auto msg = createMsg(MessageType::ADD_SHIP);

	for(const auto& ship : shipVec) {
		auto newShip = msg->add_ships();
		for(const auto& segment : ship) {
			newShip->add_x(segment.first);
			newShip->add_y(segment.second);
		}
	}
	send(msg);
}

void ClientOutput::sendHit(std::pair<int, int> hitCoordinates) {

	LOG(INFO) << "Sending HIT";
	auto msg = createMsg(MessageType::HIT);
	msg->set_x(hitCoordinates.first);
	msg->set_y(hitCoordinates.second);
	send(msg);
}
