/*
 * ConnectionBridge.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "ConnectionBridge.h"
#include "Connection.h"
#include "PlayerOutput.h"
#include <vector>

ConnectionBridge::ConnectionBridge(std::shared_ptr<ships::ConnectionPool> conn, std::shared_ptr<GameEngine> engine)
				: connectionPool(conn), gameEngine(engine) {}

ConnectionBridge::~ConnectionBridge() {
	// TODO Auto-generated destructor stub
}

void ConnectionBridge::signal() {
	std::vector<ships::ConnectionPool::ConnectionPtr> connections = connectionPool->getConnection(2);
	std::shared_ptr<PlayerOutput> output1(new PlayerOutput(connections[0]));
	std::shared_ptr<PlayerOutput> output2(new PlayerOutput(connections[1]));
	gameEngine->createGame(output1, output2);
}
