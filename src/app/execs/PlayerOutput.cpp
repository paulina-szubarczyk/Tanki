/*
 * PlayerOutput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "PlayerOutput.h"

#include "glog/logging.h"

#include <stdexcept>

PlayerOutput::PlayerOutput(std::shared_ptr<ships::ProtobufConnection> connection) : connection_(connection){
	if(!connection_)
		throw new std::invalid_argument("Cannot instantiate a MessageSender with a null connection");
}

void PlayerOutput::beginGame() {

	LOG(INFO) << "Sending BEGIN";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::BEGIN);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerTurn() {

	LOG(INFO) << "Sending TURN";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::TURN);
	msg->set_turn(true);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerShipHit(int x, int y) {

	LOG(INFO) << "Sending HIT";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::HIT);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerShipSunk(int x, int y) {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::SUNK);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentShipHit(int x, int y) {

	LOG(INFO) << "Sending HIT_REPLAY";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::HIT_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentShipSunk(int x, int y) {

	LOG(INFO) << "Sending SUNK_REPLAY";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::SUNK_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentWin() {

	LOG(INFO) << "Sending OVER OPPONENT WIN";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::OVER);
	msg->set_win(false);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerWin() {

	LOG(INFO) << "Sending OVER PLAYER WIN";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::OVER);
	msg->set_win(true);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::getShips(const std::map<int, int>& shipMap) {

	LOG(INFO) << "Sending CONFIG";

	MsgPtr msg = createMsg();
	msg->set_type(MessageType::CONFIG);

	for(const auto& ship : shipMap) {

		auto* addedShip = msg->add_ships();
		addedShip->add_x(ship.first);
		addedShip->add_y(ship.second);
	}

	connection_->send(msg);
}

void PlayerOutput::gameAlreadyOccupied() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("gameAlreadyOccupied");
	connection_->send(msg);
}

void PlayerOutput::notEnoughShips(int delivered, int expected) {

	LOG(INFO) << "Sending ERROR";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("gameAlreadyOccupied");
	connection_->send(msg);
}

void PlayerOutput::playerNotReady() {

	LOG(INFO) << "Sending ERROR";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("playerNotReady");
	connection_->send(msg);
}

void PlayerOutput::oponentNotReady() {

	LOG(INFO) << "Sending ERROR";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("oponentNotReady");
	connection_->send(msg);
}

void PlayerOutput::oponentMissHit(int x, int y) {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::MISS_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerMissHit(int x, int y) {

	LOG(INFO) << "Sending MISS_REPLAY";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::MISS_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentTurn() {

	LOG(INFO) << "Sending TURN";
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::TURN);
	msg->set_turn(false);
	msg->set_this_(true);
	connection_->send(msg);
}
