/*
 * ConnectionPool.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CONNECTIONPOOL_H_
#define CONNECTIONPOOL_H_

#include <vector>
#include <memory>
#include <queue>
#include <mutex>

#include <boost/signals2/signal.hpp>

namespace net {

class ProtobufConnection;
class ConnectionObserver;

/**
 * A thread safe connection pool. A thread safe queue enables multi-threaded storage of connectionn
 * objects. A ConnectionObserver is signaled whenever the size of the queue exceeds some limit.
 */
class ConnectionPool {
public:
	//	Typedefs
	typedef std::shared_ptr<ProtobufConnection> ConnectionPtr;
	typedef std::queue<ConnectionPtr> QueueType;
	typedef std::shared_ptr<QueueType> QueuePtr;
	typedef std::unique_lock<std::mutex> Lock;
	typedef std::shared_ptr<ConnectionObserver> ObserverPtr;
	typedef boost::signals2::signal<void(void)> SignalType;

public:
	ConnectionPool();
	virtual ~ConnectionPool() = default;

	size_t size();
	void addConnection(ConnectionPtr connection);

	/**
	 * Pops a connection from the queue and retrieves it.
	 */
	ConnectionPtr getConnection();

	/**
	 * Pops up to num connections from the queue and retrieves them.
	 */
	std::vector<ConnectionPtr> getConnection(int num);

	/**
	 * Returns a queue size after exceeding which a signal is dispatched
	 */
	size_t getConnsToSignal() const;

	/**
	 * Sets a connection limit after exceeding which a signal is dispatched
	 */
	void setConnsToSignal(size_t connsToSignal);

	/**
	 * Registers an observer that gets signaled whenever a queue size limit is exceeded
	 */
	void registerConnectionObserver(ObserverPtr observer);

private:

	QueuePtr queue_;
	std::mutex mutex_;
	size_t connsToSignal_;
	SignalType signal_;
};

} /* namespace net */

#endif /* CONNECTIONPOOL_H_ */
