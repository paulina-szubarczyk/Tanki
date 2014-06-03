/*
 * PlayerOutput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "PlayerOutput.h"

#include "glog/logging.h"

PlayerOutput::PlayerOutput(std::shared_ptr<ProtobufConnection> connection) :
		IOutput(connection) {}

void PlayerOutput::beginGame() {

	LOG(INFO)<< "Sending BEGIN";
	MsgPtr msg = createMsg(MessageType::BEGIN);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::playerTurn() {

	LOG(INFO)<< "Sending TURN";
	MsgPtr msg = createMsg(MessageType::TURN);

	msg->set_turn(true);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::playerShipHit(int x, int y) {

	LOG(INFO)<< "Sending HIT";
	MsgPtr msg = createMsg(MessageType::HIT);

	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::playerShipSunk(int x, int y) {
	MsgPtr msg = createMsg(MessageType::SUNK);

	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::oponentShipHit(int x, int y) {

	LOG(INFO)<< "Sending HIT_REPLAY";
	MsgPtr msg = createMsg(MessageType::HIT_REPLAY);

	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::oponentShipSunk(int x, int y) {

	LOG(INFO)<< "Sending SUNK_REPLAY";
	MsgPtr msg = createMsg(MessageType::SUNK_REPLAY);

	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::oponentWin() {

	LOG(INFO)<< "Sending OVER OPPONENT WIN";
	MsgPtr msg = createMsg(MessageType::OVER);

	msg->set_win(false);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::playerWin() {

	LOG(INFO)<< "Sending OVER PLAYER WIN";
	MsgPtr msg = createMsg(MessageType::OVER);

	msg->set_win(true);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::setConfig(const std::map<int, int>& shipMap, int gameboardSize) {

	LOG(INFO)<< "Sending CONFIG";

	MsgPtr msg = createMsg(MessageType::CONFIG);

	msg->set_grid_size(gameboardSize);

	for(const auto& ship : shipMap) {

		auto* addedShip = msg->add_ships();
		addedShip->add_x(ship.first);
		addedShip->add_y(ship.second);
	}

	send(msg);
}

void PlayerOutput::gameAlreadyOccupied() {
	MsgPtr msg = createMsg(MessageType::ERROR);

	msg->set_error_msg("gameAlreadyOccupied");
	send(msg);
}

void PlayerOutput::notEnoughShips(int delivered, int expected) {

	LOG(INFO)<< "Sending ERROR";
	MsgPtr msg = createMsg(MessageType::ERROR);

	msg->set_error_msg("gameAlreadyOccupied");
	send(msg);
}

void PlayerOutput::playerNotReady() {

	LOG(INFO)<< "Sending ERROR";
	MsgPtr msg = createMsg(MessageType::ERROR);

	msg->set_error_msg("playerNotReady");
	send(msg);
}

void PlayerOutput::oponentNotReady() {

	LOG(INFO)<< "Sending ERROR";
	MsgPtr msg = createMsg(MessageType::ERROR);

	msg->set_error_msg("oponentNotReady");
	send(msg);
}

void PlayerOutput::oponentMissHit(int x, int y) {

	LOG(INFO) << "Sending MISS_REPLAY";
	MsgPtr msg = createMsg(MessageType::MISS_REPLAY);

	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::playerMissHit(int x, int y) {

	LOG(INFO)<< "Sending MISS_REPLAY";
	MsgPtr msg = createMsg(MessageType::MISS_REPLAY);

	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	send(msg);
}

void PlayerOutput::oponentTurn() {

	LOG(INFO)<< "Sending TURN";
	MsgPtr msg = createMsg(MessageType::TURN);

	msg->set_turn(false);
	msg->set_this_(true);
	send(msg);
}
