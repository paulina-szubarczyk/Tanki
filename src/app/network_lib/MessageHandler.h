/*
 * MessageHandler.h
 *
 *  Created on: May 9, 2014
 *      Author: Adam Kosiorek
 */

#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include "MessageHandlerPolicies.h"

#include <functional>
#include <map>

namespace ships {

/**
 * MessageHandler allows handling protobuf messages based on their type field.
 * It accepts a message type resolving method and then type-based message handling methods
 * Execution of the message handles is policy based and can be either direct or relayed to another object.
 */
template<typename K, typename M, template<typename M> class ExecPolicy = DirectExecutePolicy>
class MessageHandler : private ExecPolicy<M> {
public:
	typedef K KeyType;
	typedef M MsgType;
	typedef std::function<void(const MsgType&)> HandlerType;

private:
	typedef std::function<KeyType(const MsgType&)> ResolverType;
	typedef std::map<KeyType, HandlerType> HandlerMapType;

public:
	MessageHandler();
	virtual ~MessageHandler();

	/**
	 * Sets a type resolution method
	 * @param fun	Type resolution method. It should take an MsgType as a formal argument and return its type
	 */
	void setTypeMethod(ResolverType fun);

	/**
	 * Public method that uses the TypeMethod to resolve a type of a given message
	 */
	KeyType resolveType(const MsgType& message) const;

	/**
	 * Adds a message handler
	 */
	bool addMsgHandler(KeyType type, HandlerType handler);

	/**
	 * Returns a map of the message handlers
	 */
	const HandlerMapType& getMsgHandlers() const;

	/**
	 * Handles a message
	 */
	void handleMsg(const MsgType& message) const;

private:
	ResolverType typeFun_;
	HandlerMapType msgHandlers_;

};

} /* namespace ships */

#endif /* MESSAGEHANDLER_H_ */
