/*
 * MessageHandlerPolicies.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "MessageHandlerPolicies.h"
#include <boost/asio.hpp>

namespace ships {

template<typename MsgType>
RelayExecutePolicy<MsgType>::RelayExecutePolicy(ServicePtr service)
	: service_(service) {};

template<typename MsgType> void RelayExecutePolicy<MsgType>::execute
(const std::function<void(const MsgType&)>& fun, const MsgType& msg) {

	service_->dispatch(std::bind(fun, msg));
};

template<typename MsgType>
auto RelayExecutePolicy<MsgType>::getService() const -> ServicePtr{
	return service_;
}

template<typename MsgType>
void RelayExecutePolicy<MsgType>::setService(ServicePtr service) {
	service_ = service;
}

} /* namespace ships */
