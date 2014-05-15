/*
 * MessageHandlerPolicies.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef MESSAGEHANDLERPOLICIES_H_
#define MESSAGEHANDLERPOLICIES_H_

#include <memory>
#include <functional>

namespace boost { namespace asio { class io_service; } }

namespace ships {

/**
 * A direct execute policy for the MessageHandler class. It directly executes the handlers
 */
template<typename MsgType>
class DirectExecutePolicy {
protected:
	void execute(const std::function<void(const MsgType&)>& fun, const MsgType& msg) {

		fun(msg);
	}

	DirectExecutePolicy() = default;
	~DirectExecutePolicy() = default;
};

/**
 * A relaying execute policy for the MesageHandler class. It relays execution of the handler to an
 * boost::asio::io_service object
 */
template<typename MsgType>
class RelayExecutePolicy {
public:
	typedef std::shared_ptr<boost::asio::io_service> ServicePtr;

	ServicePtr getService() const;
	void setService(ServicePtr service);
protected:

	void execute(const std::function<void(const MsgType&)>& fun, const MsgType& msg);

	RelayExecutePolicy(ServicePtr service);
	~RelayExecutePolicy() = default;

private:
	ServicePtr service_;
};

} /* namespace ships */

#endif /* MESSAGEHANDLERPOLICIES_H_ */
