/*
 * ProtobufConnectionFactory.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "ProtobufConnectionFactory.h"
#include "ProtobufConnection.h"
#include "IoHarbour.h"

namespace net {

ProtobufConnectionFactory::ProtobufConnectionFactory(HarbourPtr harbour)
	: harbour_(harbour), msgHandler_(nullptr) {}

auto ProtobufConnectionFactory::getMsgHandler() const -> MsgHandlerPtr {
	return msgHandler_;
}

void ProtobufConnectionFactory::setMsgHandler(MsgHandlerPtr msgHandler) {
	msgHandler_ = msgHandler;
}

auto ProtobufConnectionFactory::createConnection() const -> ConnectionPtr {

	return std::make_shared<ProtobufConnection>(harbour_, msgHandler_ ? msgHandler_->clone() : nullptr);
}

auto ProtobufConnectionFactory::getHarbour() const -> HarbourPtr {
	return harbour_;
}

void ProtobufConnectionFactory::setHarbour(HarbourPtr harbour) {
	harbour_ = harbour;
}

} /* namespace net */
