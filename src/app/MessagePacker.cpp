/*
 * PackedMessage.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Adam Kosiorek
 */

#include "MessagePacker.h"
#include "test.pb.h"
#include "message.pb.h"

template<class MsgType, class BuffType>
const unsigned MessagePacker<MsgType, BuffType>::HEADER_SIZE = 4;

template<class MsgType, class BuffType>
MessagePacker<MsgType, BuffType>::MessagePacker() : msg_(new MsgType()) {};

template<class MsgType, class BuffType>
MessagePacker<MsgType, BuffType>::MessagePacker(MsgPtr msg) {
	if(msg == nullptr) throw new std::logic_error("Cannot pack a null message");
	msg_ = std::move(msg);
};

template<class MsgType, class BuffType>
void MessagePacker<MsgType, BuffType>::setMsg(MsgPtr msg) {
	if(msg == nullptr) throw new std::logic_error("Cannot pack a null message");
	msg_ = std::move(msg);
}

template<class MsgType, class BuffType>
auto MessagePacker<MsgType, BuffType>::getMsg() const -> MsgPtr {
	return msg_;
}

template<class MsgType, class BuffType>
bool MessagePacker<MsgType, BuffType>::pack(BuffType& buf) const {
	if (!msg_->IsInitialized())
		throw new std::logic_error("Cannot pack a null message");

	unsigned msg_size = msg_->ByteSize();
	buf.resize(HEADER_SIZE + msg_size);
	encodeHeader(buf, msg_size);
	return msg_->SerializeToArray(&buf[HEADER_SIZE], msg_size);
}

template<class MsgType, class BuffType>
unsigned MessagePacker<MsgType, BuffType>::decodeHeader(const BuffType& buf) const {
	if (buf.size() < HEADER_SIZE)
		throw new std::logic_error("Buffer's size should be >= 4");

	unsigned msg_size = 0;
	for (unsigned i = 0; i < HEADER_SIZE; ++i)
		msg_size = msg_size * 256 + (static_cast<unsigned>(buf[i]) & 0xFF);
	return msg_size;
}

template<class MsgType, class BuffType>
bool MessagePacker<MsgType, BuffType>::unpack(const BuffType& buf) {
	return msg_->ParseFromArray(&buf[HEADER_SIZE],
			buf.size() - HEADER_SIZE);
}

template<class MsgType, class BuffType>
void MessagePacker<MsgType, BuffType>::encodeHeader(BuffType& buf, unsigned size) const {
	assert(buf.size() >= HEADER_SIZE);
	buf[0] = static_cast<uint8_t>((size >> 24) & 0xFF);
	buf[1] = static_cast<uint8_t>((size >> 16) & 0xFF);
	buf[2] = static_cast<uint8_t>((size >> 8) & 0xFF);
	buf[3] = static_cast<uint8_t>(size & 0xFF);
}

template class MessagePacker<TestMsg>;
template class MessagePacker<DataMsg>;
