/*
 * MessageHandler.cpp
 *
 *  Created on: May 9, 2014
 *      Author: Adam Kosiorek
 */

#include "MessageHandler.h"
#include "message.pb.h"

#include "glog/logging.h"

#include "stdexcept"

namespace net {

template<typename K, typename M, template<typename M> class ExecPolicy>
void MessageHandler<K, M, ExecPolicy>::setTypeMethod(ResolverType fun) {

	typeFun_ = fun;
}

template<typename K, typename M, template<typename M> class ExecPolicy>
auto MessageHandler<K, M, ExecPolicy>::resolveType(
		const MsgType& message) const -> KeyType {

	return typeFun_(message);
}

template<typename K, typename M, template<typename M> class ExecPolicy>
bool MessageHandler<K, M, ExecPolicy>::addMsgHandler(KeyType type,
		HandlerType handler) {

	if (msgHandlers_.find(type) != msgHandlers_.end()) {
		return false;
	}
	msgHandlers_.insert( { type, handler });
	return true;
}

template<typename K, typename M, template<typename M> class ExecPolicy>
auto MessageHandler<K, M, ExecPolicy>::getMsgHandlers() const -> const HandlerMapType& {

	return msgHandlers_;
}

template<typename K, typename M, template<typename M> class ExecPolicy>
void MessageHandler<K, M, ExecPolicy>::handleMsg(const MsgType& message) const {

	try {
		auto type = resolveType(message);
		LOG(INFO)<< "Handling message type " << type;
		msgHandlers_.at(type)(message);
	} catch (std::bad_function_call& err) {

		LOG(ERROR)<< err.what();
		throw;
	}
}

template<typename K, typename M, template<typename M> class ExecPolicy>
auto MessageHandler<K, M, ExecPolicy>::clone() const -> ThisTypePtr {

	auto msgHandler = std::make_shared<MessageHandler>();
	msgHandler->setTypeMethod(typeFun_);
	for (const auto& pair : msgHandlers_) {
		msgHandler->addMsgHandler(pair.first, pair.second);
	}
	return msgHandler;
}

template class MessageHandler<MessageType, DataMsg, DirectExecutePolicy> ;

} /* namespace net */
