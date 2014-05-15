/*
 * ProtobufConnectionFactory.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "ProtobufConnectionFactory.h"
#include "ProtobufConnection.h"

namespace ships {

ProtobufConnectionFactory::ProtobufConnectionFactory(HarbourPtr harbour)
	: ConnectionFactory(harbour), msgHandler_(nullptr) {}

auto ProtobufConnectionFactory::getMsgHandler() const -> MsgHandlerPtr {
	return msgHandler_;
}

void ProtobufConnectionFactory::setMsgHandler(MsgHandlerPtr msgHandler) {
	msgHandler_ = msgHandler;
}

auto ProtobufConnectionFactory::createConnection() const -> ConnectionPtr {

	return std::shared_ptr<Connection>(new ProtobufConnection(harbour_, msgHandler_));
}

} /* namespace ships */
