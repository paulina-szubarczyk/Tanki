/*
 * ServerConnection.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Adam Kosiorek
 */

#include "ProtobufConnection.h"
#include "MessagePacker.h"

#include "glog/logging.h"

using namespace std::placeholders;

namespace ships {

ProtobufConnection::ProtobufConnection(HarbourPtr harbour, MsgHandlerPtr msgHandler)
	: Connection(harbour),
	  msgHandler_(msgHandler) {}

void ProtobufConnection::send(std::shared_ptr<DataMsg> msg) {

	std::vector<uint8_t> buffer;
	msgPacker_.setMsg(msg);
	msgPacker_.pack(buffer);
	Connection::send(buffer);
}

void ProtobufConnection::onAccept(const std::string & host, uint16_t port) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << host << ":" << port;

	// Start the next receive
	receive();
}

void ProtobufConnection::onConnect(const std::string & host, uint16_t port) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << host << ":" << port;

	// Start the next receive
	receive();
}

void ProtobufConnection::onSend(const std::vector<uint8_t> & buffer) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes";
}

void ProtobufConnection::onReceive(std::vector<uint8_t> & buffer) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes";

	receive();
}

void ProtobufConnection::onTimer(const milliseconds& delta) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << delta.count();
}

void ProtobufConnection::onError(const boost::system::error_code & error) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << error;
}

void ProtobufConnection::startReceive(int32_t totalBytes) {

	auto wrappedHeaderHandler = strand_.wrap(std::bind(
			&ProtobufConnection::handleReceiveHeader, std::dynamic_pointer_cast<ProtobufConnection>(shared_from_this()), _1));

    receiveBuffer_.resize(msgPacker_.HEADER_SIZE);
    async_read(socket_, buffer(receiveBuffer_), wrappedHeaderHandler);
}

void ProtobufConnection::startReceiveBody(int32_t totalBytes) { //header

	receiveBuffer_.resize(msgPacker_.HEADER_SIZE + totalBytes);
	mutable_buffers_1 buf = buffer(
			&receiveBuffer_[msgPacker_.HEADER_SIZE], totalBytes);

	auto wrappedBodyHandler = strand_.wrap(std::bind(
			&ProtobufConnection::handleReceiveBody, std::dynamic_pointer_cast<ProtobufConnection>(shared_from_this()), _1));

	async_read(socket_, buf, wrappedBodyHandler);
}

void ProtobufConnection::handleReceiveHeader(const boost::system::error_code & error) {

	startReceiveBody(msgPacker_.decodeHeader(receiveBuffer_));
}

void ProtobufConnection::handleReceiveBody(const boost::system::error_code & error) {

	if(msgPacker_.unpack(receiveBuffer_))
		msgHandler_->handleMsg(*msgPacker_.getMsg());

	startReceive();
}

} /* namespace ships */
