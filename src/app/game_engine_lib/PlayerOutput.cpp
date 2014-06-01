/*
 * PlayerOutput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "PlayerOutput.h"
#include <stdexcept>
PlayerOutput::PlayerOutput(std::shared_ptr<ships::ProtobufConnection> connection) : connection_(connection){
	if(!connection_)
		throw new std::invalid_argument("Cannot instantiate a MessageSender with a null connection");
}

PlayerOutput::~PlayerOutput() {
}

void PlayerOutput::beginGame() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::BEGIN);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerTurn() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::TURN);
	msg->set_turn(true);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerShipHit(int x, int y) {
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
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::HIT_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentShipSunk(int x, int y) {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::SUNK_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentWin() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::OVER);
	msg->set_win(false);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::playerWin() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::OVER);
	msg->set_win(true);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::gameAlreadyOccupied() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("gameAlreadyOccupied");
	connection_->send(msg);
}

void PlayerOutput::notEnoughShips(int delivered, int expected) {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("gameAlreadyOccupied");
	connection_->send(msg);
}

void PlayerOutput::playerNotReady() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::ERROR);
	msg->set_error_msg("playerNotReady");
	connection_->send(msg);
}

void PlayerOutput::oponentNotReady() {
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
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::MISS_REPLAY);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void PlayerOutput::oponentTurn() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::TURN);
	msg->set_turn(false);
	msg->set_this_(true);
	connection_->send(msg);
}
