/*
 * Acceptor.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Adam Kosiorek
 */

#include "Acceptor.h"
#include "IoHarbour.h"
#include "ProtobufConnection.h"

#include "boost/lexical_cast.hpp"

namespace net {

using namespace std::placeholders;

Acceptor::Acceptor(HarbourPtr harbour) :
		harbour_(harbour), acceptor_(harbour->getService()), strand_(
				harbour->getService()), timer_(harbour->getService()), timerInterval_(
				1000), error_(0) {
}

std::shared_ptr<IoHarbour> Acceptor::getHarbour() {
	return harbour_;
}

ip::tcp::acceptor& Acceptor::getAcceptor() {
	return acceptor_;
}

strand& Acceptor::getStrand() {
	return strand_;
}

void Acceptor::setTimerInterval(int32_t timerInterval) {
	timerInterval_ = timerInterval;
}

int32_t Acceptor::getTimerInterval() const {
	return timerInterval_;
}

bool Acceptor::hasError() {
	return error_ != 0;
}

void Acceptor::listen(const std::string& host, const uint16_t& port) {

	ip::tcp::resolver resolver(harbour_->getService());
	ip::tcp::resolver::query query(host,
			boost::lexical_cast<std::string>(port));
	ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(ip::tcp::acceptor::reuse_address(false));
	acceptor_.bind(endpoint);
	acceptor_.listen(socket_base::max_connections);
	startTimer();
}

void Acceptor::accept(std::shared_ptr<ProtobufConnection> connection) {
	strand_.post(
			std::bind(&Acceptor::dispatchAccept, shared_from_this(),
					connection));
}

void Acceptor::stop() {
	strand_.post(
			std::bind(&Acceptor::handleTimer, shared_from_this(),
					error::connection_reset));
}

void Acceptor::startTimer() {
	lastTimerEvent_ = steady_clock::now();
	timer_.expires_from_now(milliseconds(timerInterval_));
	timer_.async_wait(
			strand_.wrap(
					std::bind(&Acceptor::handleTimer, shared_from_this(), _1)));
}

void Acceptor::startError(const boost::system::error_code& error) {
	if (error_ != 0)
		return;

	boost::system::error_code ec;
	acceptor_.cancel(ec);
	acceptor_.close(ec);
	timer_.cancel(ec);
	onError(error);
}

void Acceptor::dispatchAccept(std::shared_ptr<ProtobufConnection> connection) {

	acceptor_.async_accept(connection->getSocket(),
			connection->getStrand().wrap(
					std::bind(&Acceptor::handleAccept, shared_from_this(), _1,
							connection)));
}

void Acceptor::handleTimer(const boost::system::error_code& error) {

	if (handleError(error))
		return;

	onTimer(duration_cast<milliseconds>(steady_clock::now() - lastTimerEvent_));
	startTimer();
}

void Acceptor::handleAccept(const boost::system::error_code& error,
		std::shared_ptr<ProtobufConnection> connection) {

	if (handleError(error))
		return;

	if (connection->getSocket().is_open()) {
		connection->startTimer();
		auto remoteEndpoint = connection->getSocket().remote_endpoint();
		if (onAccept(connection, remoteEndpoint.address().to_string(),
				remoteEndpoint.port())) {

			connection->onAccept(
					acceptor_.local_endpoint().address().to_string(),
					acceptor_.local_endpoint().port());
		}
	} else
		startError(error);

}

bool Acceptor::handleError(const boost::system::error_code& error) {

	if (error || hasError() || harbour_->hasStopped()) {
		startError(error);
		return true;
	}
	return false;
}

} /* namespace net */
