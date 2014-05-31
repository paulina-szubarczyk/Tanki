/*
 * MessageSender.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "MessageSender.h"
#include <stdexcept>

namespace ships {

MessageSender::MessageSender(ConnectionPtr connection) : connection_(connection) {

	if(!connection_)
		throw new std::invalid_argument("Cannot instantiate a MessageSender with a null connection");
}

auto MessageSender::getConnection() const -> ConnectionPtr{
	return connection_;
}

void MessageSender::sendHitThisXY(int x, int y) {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::HIT);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void MessageSender::sendHitThatXY(int x, int y) {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::HIT);
	msg->set_x(x);
	msg->set_y(y);
	msg->set_this_(true);
	connection_->send(msg);
}

void MessageSender::sendWin() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::RESULT);
	msg->set_win(true);
	connection_->send(msg);
}

void MessageSender::sendLose() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::RESULT);
	msg->set_win(false);
	connection_->send(msg);
}

void MessageSender::sendOtherPlayerLeft() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::LEFT);
	connection_->send(msg);
}

void MessageSender::sendGameOver() {
	MsgPtr msg = createMsg();
	msg->set_type(MessageType::OVER);
	connection_->send(msg);
}

void MessageSender::sendGetShips() {
	MsgPtr msg = createMsg();
	//msg->set_type(MessageType::GET_SHIPS);
	//connection_->send(msg);
}

void MessageSender::setConnection(ConnectionPtr connection) {
	connection_ = connection;
}


auto MessageSender::createMsg() const -> MsgPtr {
	return MsgPtr(new DataMsg());
}

} /* namespace ships */
