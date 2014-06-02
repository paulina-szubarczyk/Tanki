/*
 * ConnectionBridge.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "ConnectionBridge.h"
#include "Connection.h"
#include "PlayerInput.h"
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


	std::vector<std::shared_ptr<PlayerInput>> inputs = {
			std::make_shared<PlayerInput>(connections[0]->getMsgHandler()),
			std::make_shared<PlayerInput>(connections[1]->getMsgHandler())
	};

	std::vector<std::shared_ptr<GamePlayerOutput>> outputs = {
			std::make_shared<PlayerOutput>(connections[0]),
			std::make_shared<PlayerOutput>(connections[1])
	};

	LOG(INFO) << "Relaying " << connections.size() << " connections";
	gameEngine->createGame(outputs, inputs);
}
