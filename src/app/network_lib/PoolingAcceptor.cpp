/*
 * PoolingAcceptor.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "PoolingAcceptor.h"
#include "ConnectionPool.h"
#include "ProtobufConnectionFactory.h"
#include "ProtobufConnection.h"
#include "glog/logging.h"
namespace net {

PoolingAcceptor::PoolingAcceptor(HarbourPtr harbour, PoolPtr pool,
		FactoryPtr factory, int poolSize) :
		Acceptor(harbour), pool_(pool), factory_(factory), poolSize_(poolSize), initialized_(
				false) {
}

bool PoolingAcceptor::onAccept(std::shared_ptr<ProtobufConnection> connection,
		const std::string & host, uint16_t port) {
	LOG(INFO)<< "[" << __FUNCTION__ << "] " << host << ":" << port;

	pool_->addConnection(connection);
	this->accept(factory_->createConnection());
	return true;
}

void PoolingAcceptor::onTimer(const milliseconds& delta) {
	LOG(INFO)<< "[" << __FUNCTION__ << "] " << delta.count();
}

void PoolingAcceptor::onError(const boost::system::error_code & error) {
	LOG(INFO)<< "[" << __FUNCTION__ << "] " << error;
}

void PoolingAcceptor::listen(const std::string& host, const uint16_t& port) {

	Acceptor::listen(host, port);
	if (!initialized_)
		initialize();
}

void PoolingAcceptor::initialize() {
	for (int i = 0; i < poolSize_; ++i)
		this->accept(factory_->createConnection());

	initialized_ = true;
}

} /* namespace net */
