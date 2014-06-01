/*
 * MessageHandler.cpp
 *
 *  Created on: May 9, 2014
 *      Author: Adam Kosiorek
 */

#include "MessageHandler.h"
#include "message.pb.h"

namespace ships {

template<typename K, typename M, template<typename M> class ExecPolicy>
MessageHandler<K, M, ExecPolicy>::MessageHandler() {
	// TODO Auto-generated constructor stub

}

template<typename K, typename M, template<typename M> class ExecPolicy>
MessageHandler<K, M, ExecPolicy>::~MessageHandler() {
	// TODO Auto-generated destructor stub
}

template<typename K, typename M, template<typename M> class ExecPolicy>
void MessageHandler<K, M, ExecPolicy>::setTypeMethod(ResolverType fun) {

	typeFun_ = fun;
}

template<typename K, typename M, template<typename M> class ExecPolicy>
auto MessageHandler<K, M, ExecPolicy>::resolveType(const MsgType& message) const -> KeyType {

	return typeFun_(message);
}

template<typename K, typename M, template<typename M> class ExecPolicy>
bool MessageHandler<K, M, ExecPolicy>::addMsgHandler(KeyType type, HandlerType handler) {

	if(msgHandlers_.find(type) != msgHandlers_.end()) {
		return false;
	}

	msgHandlers_.insert({type, handler});
	return true;
}

template<typename K, typename M, template<typename M> class ExecPolicy>
auto MessageHandler<K, M, ExecPolicy>::getMsgHandlers() const -> const HandlerMapType& {

	return msgHandlers_;
}

template<typename K, typename M, template<typename M> class ExecPolicy>
void MessageHandler<K, M, ExecPolicy>::handleMsg(const MsgType& message) const {

	msgHandlers_.at(resolveType(message))(message);
}

template class MessageHandler<MessageType, DataMsg, DirectExecutePolicy>;

} /* namespace ships */
