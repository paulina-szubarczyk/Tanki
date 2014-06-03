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
#include "GamesManager.h"

using namespace net;

class ConnectionBridge : public ConnectionObserver {
public:
	ConnectionBridge(std::shared_ptr<ConnectionPool> conn, std::shared_ptr<game::GamesManager> engine);
	virtual ~ConnectionBridge() = default;

	virtual void signal();

private:
	std::shared_ptr<ConnectionPool> connectionPool;
	std::shared_ptr<game::GamesManager> gamesManager;
};

#endif /* CONNECTIONBRIDGE_H_ */
