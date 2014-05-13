/*
 * BasicAcceptor.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Adam Kosiorek
 */

#include "BasicAcceptor.h"

#include "glog/logging.h"

namespace ships {

BasicAcceptor::BasicAcceptor(std::shared_ptr<ships::IoHarbour> harbour)
		: Acceptor(harbour) {}

bool BasicAcceptor::onAccept(std::shared_ptr<ships::Connection> connection,
		const std::string & host, uint16_t port) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << host << ":" << port;

	return true;
}

void BasicAcceptor::onTimer(const milliseconds& delta) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << delta.count();
}

void BasicAcceptor::onError(const boost::system::error_code & error) {
	LOG(INFO) << "[" << __FUNCTION__ << "] " << error;
}


} /* namespace ships */
