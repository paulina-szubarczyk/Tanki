/*
 * ConnectionBridge.h
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#ifndef CONNECTIONBRIDGE_H_
#define CONNECTIONBRIDGE_H_

#include "ConnectionObserver.h"
#include "ConnectionPool.h"
#include "GameEngine.h"


class ConnectionBridge : public ships::ConnectionObserver {
public:
	ConnectionBridge(std::shared_ptr<ships::ConnectionPool> conn, std::shared_ptr<GameEngine> engine);
	virtual ~ConnectionBridge();

	virtual void signal();

private:
	std::shared_ptr<ships::ConnectionPool> connectionPool;
	std::shared_ptr<GameEngine> gameEngine;
};

#endif /* CONNECTIONBRIDGE_H_ */
