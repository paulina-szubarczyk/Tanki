/*
 * ConnectionPool.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "ConnectionPool.h"
#include "ConnectionObserver.h"
#include "ProtobufConnection.h"

#include "glog/logging.h"

namespace ships {

ConnectionPool::ConnectionPool() : queue_(new QueueType()), connsToSignal_(1) {}

size_t ConnectionPool::size() {
	return queue_->size();
}

void ConnectionPool::registerConnectionObserver(ObserverPtr observer) {
	LOG(INFO) << "Registering observer";
	signal_.connect(SignalType::slot_type(&ConnectionObserver::signal, observer.get()).track_foreign(observer));
}

} /* namespace ships */

void ships::ConnectionPool::addConnection(ConnectionPtr connection) {
	Lock lock(mutex_);
	LOG(INFO) << "Adding connection";
	queue_->push(connection);

	if(queue_->size() >= connsToSignal_) {
		LOG(INFO) << "Signaling";
		lock.unlock();
		signal_();
	}
}

auto ships::ConnectionPool::getConnection() -> ConnectionPtr {
	Lock lock(mutex_);
	LOG(INFO) << "Returning a connection";
	auto head =  queue_->front();
	queue_->pop();
	return head;
}

size_t ships::ConnectionPool::getConnsToSignal() const {
	return connsToSignal_;
}

void ships::ConnectionPool::setConnsToSignal(size_t connsToSignal) {
	connsToSignal_ = connsToSignal;
}

auto ships::ConnectionPool::getConnection(int num) -> std::vector<ConnectionPtr>{
	Lock lock(mutex_);
	LOG(INFO) << "Returning " << num << " connections";
	std::vector<ConnectionPtr> conns;
	while(num > 0 && !queue_->empty()) {
		conns.push_back(queue_->front());
		queue_->pop();
		--num;
	}
	return conns;
}
