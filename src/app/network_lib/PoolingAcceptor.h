/*
 * PoolingAcceptor.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef POOLINGACCEPTOR_H_
#define POOLINGACCEPTOR_H_

#include "Acceptor.h"

namespace ships {

class ConnectionPool;
class ProtobufConnectionFactory;
class ProtobufConnection;

/**
 * A concrete Acceptor class.
 * It listens for mutiple connection at the given endpoint. Upon accepting a connection it is
 * moved to a ConnectionPool and a new Connection is spawned at its place
 */
class PoolingAcceptor : public Acceptor {
public:	//	Typedefs
	typedef std::shared_ptr<ConnectionPool> PoolPtr;
	typedef std::shared_ptr<ProtobufConnectionFactory> FactoryPtr;


public:
	PoolingAcceptor(HarbourPtr harbour, PoolPtr pool, FactoryPtr factory, int poolSize = 4);
	virtual ~PoolingAcceptor() = default;

	virtual void listen(const std::string& host, const uint16_t& port);

private:
	bool onAccept(std::shared_ptr<ships::ProtobufConnection> connection,
			const std::string & host, uint16_t port) override;
	void onTimer(const milliseconds& delta) override;
	void onError(const boost::system::error_code & error) override;

	void initialize();

	PoolPtr pool_;
	FactoryPtr factory_;
	int poolSize_;
	bool initialized_;
};

} /* namespace ships */

#endif /* POOLINGACCEPTOR_H_ */
