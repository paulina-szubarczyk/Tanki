/*
 * ConnectionBridge.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "ConnectionBridge.h"
#include "Connection.h"
#include "PlayerOutput.h"
#include "ProtobufConnection.h"
#include <vector>

#include "glog/logging.h"

ConnectionBridge::ConnectionBridge(std::shared_ptr<ships::ConnectionPool> conn,
		std::shared_ptr<GameEngine> engine) :
		connectionPool(conn), gameEngine(engine) {}

void ConnectionBridge::signal() {

	LOG(INFO) << "Received signal";

	auto connections =	connectionPool->getConnection(2);

	LOG(INFO) << "Relaying " << connections.size() << " connections";
	gameEngine->createGame(
			std::make_shared<PlayerOutput>(connections[0]),
			std::make_shared<PlayerOutput>(connections[1])
	);
}
