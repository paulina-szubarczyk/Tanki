/*
 * MessageHandler.h
 *
 *  Created on: May 9, 2014
 *      Author: Adam Kosiorek
 */

#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include <functional>
#include <map>

namespace ships {

template<typename MsgType>
class DirectExecutePolicy {
protected:
	void execute(const std::function<void(const MsgType&)>& fun, const MsgType& msg) {

		fun(msg);
	}

	DirectExecutePolicy() = default;
	~DirectExecutePolicy() = default;
};

template<typename MsgType>
class RelayExecutePolicy {
protected:
	void execute(const std::function<void(const MsgType&)>& fun, const MsgType& msg) {

		fun(msg);
	};

	RelayExecutePolicy() = default;
	~RelayExecutePolicy() = default;
};

template<typename K, typename M, template<typename M> class ExecPolicy = DirectExecutePolicy>
class MessageHandler : private ExecPolicy<M> {
public:
	typedef K KeyType;
	typedef M MsgType;

private:
	typedef std::function<KeyType(const MsgType&)> ResolverType;
	typedef std::function<void(const MsgType&)> HandlerType;
	typedef std::map<KeyType, HandlerType> HandlerMapType;

public:
	MessageHandler();
	virtual ~MessageHandler();

	void setTypeMethod(ResolverType fun);
	KeyType resolveType(const MsgType& message) const;
	bool addMsgHandler(KeyType type, HandlerType handler);
	const HandlerMapType& getMsgHandlers() const;
	void handleMsg(const MsgType& message) const;

private:
	ResolverType typeFun_;
	HandlerMapType msgHandlers_;

};

} /* namespace ships */

#endif /* MESSAGEHANDLER_H_ */
