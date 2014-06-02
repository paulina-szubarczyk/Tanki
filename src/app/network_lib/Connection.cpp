/*
 * Connection.cpp
 *
 *  Created on: May 11, 2014
 *      Author: Adam Kosiorek
 */

#include "Connection.h"
#include "IoHarbour.h"

#include <boost/lexical_cast.hpp>

#include <functional>

using namespace std::placeholders;

namespace net {

Connection::Connection(HarbourPtr harbour) :
		harbour_(harbour), strand_(harbour_->getService()), socket_(
				harbour_->getService()), timer_(harbour_->getService()), receiveBufferSize_(
				4096), timerInterval_(1000), error_(0) {
}

bool Connection::hasError() const {
	return error_;
}

auto Connection::getHarbour() const -> HarbourPtr {
	return harbour_;
}

int Connection::getReceiveBufferSize() const {
	return receiveBufferSize_;
}

void Connection::setReceiveBufferSize(int receiveBufferSize) {
	receiveBufferSize_ = receiveBufferSize;
}

const ip::tcp::socket& Connection::getSocket() const {
	return socket_;
}

ip::tcp::socket& Connection::getSocket() {
	return const_cast<ip::tcp::socket&>(static_cast<const Connection*>(this)->getSocket());
}

const strand& Connection::getStrand() const {
	return strand_;
}

strand& Connection::getStrand() {
	return const_cast<strand&>(static_cast<const Connection*>(this)->getStrand());
}

int Connection::getTimerInterval() const {
	return timerInterval_;
}

void Connection::setTimerInterval(int timerInterval) {
	timerInterval_ = timerInterval;
}

void Connection::bind(const std::string& ip, uint16_t port) {

	ip::tcp::endpoint endpoint(ip::address::from_string(ip), port);
	socket_.open(endpoint.protocol());
	socket_.set_option(ip::tcp::acceptor::reuse_address(false));
	socket_.bind(endpoint);
}

void Connection::connect(const std::string& host, uint16_t port) {

	ip::tcp::resolver resolver(harbour_->getService());
	ip::tcp::resolver::query query(host,
			boost::lexical_cast<std::string>(port));

	socket_.async_connect(*resolver.resolve(query),
			strand_.wrap(
					std::bind(&Connection::handleConnect, shared_from_this(),
							_1)));
}

void Connection::send(const std::vector<uint8_t>& buffer) {

	strand_.post(
			std::bind(&Connection::dispatchSend, shared_from_this(), buffer));
}

void Connection::receive(int totalBytes) {

	strand_.post(
			std::bind(&Connection::dispatchReceive, shared_from_this(),
					totalBytes));
}

void Connection::disconnect() {
	strand_.post(
			std::bind(&Connection::handleTimer, shared_from_this(),
					error::connection_reset));
}

void Connection::startSend() {

	if (pendingSends_.empty())
		return;

	auto writeBuffer = buffer(pendingSends_.front());
	auto wrappedSendHandler = strand_.wrap(
			std::bind(&Connection::handleSend, shared_from_this(), _1,
					pendingSends_.begin()));

	async_write(socket_, writeBuffer, wrappedSendHandler);
}

void Connection::startError(const boost::system::error_code& error) {
	boost::system::error_code ec;
	socket_.shutdown(ip::tcp::socket::shutdown_both, ec);
	socket_.close(ec);
	timer_.cancel(ec);
	onError(error);
}

void Connection::startReceive(int32_t totalBytes) {

	auto wrappedReceptionHandler = strand_.wrap(
			std::bind(&Connection::handleReceive, shared_from_this(), _1, _2));

	if (totalBytes > 0) {

		receiveBuffer_.resize(totalBytes);
		async_read(socket_, buffer(receiveBuffer_), wrappedReceptionHandler);
	} else {

		receiveBuffer_.resize(receiveBufferSize_);
		socket_.async_read_some(buffer(receiveBuffer_),
				wrappedReceptionHandler);
	}

}

void Connection::startTimer() {
	lastTimerEvent_ = steady_clock::now();
	timer_.expires_from_now(milliseconds(timerInterval_));
	timer_.async_wait(
			strand_.wrap(
					std::bind(&Connection::dispatchTimer, shared_from_this(),
							_1)));
}

void Connection::dispatchSend(std::vector<uint8_t> buffer) {

	bool shouldStartSend = pendingSends_.empty();
	pendingSends_.push_back(buffer);
	if (shouldStartSend)
		startSend();
}

void Connection::dispatchReceive(int32_t totalBytes) {

	bool shouldStartReceive = pendingReceives_.empty();
	pendingReceives_.push_back(totalBytes);
	if (shouldStartReceive)
		startReceive(totalBytes);
}

void Connection::dispatchTimer(const boost::system::error_code& error) {
	strand_.post(
			std::bind(&Connection::handleTimer, shared_from_this(), error));
}

void Connection::handleConnect(const boost::system::error_code& error) {

	if (handleError(error))
		return;

	if (socket_.is_open())
		onConnect(socket_.remote_endpoint().address().to_string(),
				socket_.remote_endpoint().port());
	else
		startError(error);
}

bool Connection::handleError(const boost::system::error_code& error) {

	if (error || hasError() || harbour_->hasStopped()) {
		startError(error);
		return true;
	}
	return false;
}

void Connection::handleSend(const boost::system::error_code& error,
		std::list<std::vector<uint8_t> >::iterator it) {

	if (handleError(error))
		return;

	onSend(*it);
	pendingSends_.erase(it);
	startSend();
}

void Connection::handleReceive(const boost::system::error_code& error,
		int actualBytes) {

	if (handleError(error))
		return;

	receiveBuffer_.resize(actualBytes);
	onReceive(receiveBuffer_);
	pendingReceives_.pop_front();
	if (!pendingReceives_.empty())
		startReceive(pendingReceives_.front());
}

void Connection::handleTimer(const boost::system::error_code& error) {

	if (handleError(error))
		return;

	onTimer(duration_cast<milliseconds>(steady_clock::now() - lastTimerEvent_));

	startTimer();
}

} /* namespace net */
