/*
 * 	main_client.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */


#include "GameWindow.h"

#include "ProtobufConnection.h"
#include "IoHarbour.h"
#include "MessagePacker.h"
#include "MessageHandler.h"
#include "ConnectionPool.h"
#include "ProtobufConnectionFactory.h"
#include "ClientOutput.h"
#include "ClientInput.h"

#include <glog/logging.h>

using namespace ships;

int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);


	std::shared_ptr<IoHarbour> harbour(new IoHarbour());

	std::shared_ptr<MessageHandler<MessageType, DataMsg>> msgHandler(new MessageHandler<MessageType, DataMsg>());
	std::shared_ptr<ProtobufConnection> connection = std::make_shared<ProtobufConnection>(harbour, msgHandler);

//	TODO
//	connection->connect("127.0.0.1", 8081);

	std::shared_ptr<ClientOutput> clientOutput = std::make_shared<ClientOutput>(connection);
	std::shared_ptr<ClientInput> clientInput = std::make_shared<ClientInput>(clientOutput, msgHandler);

	GameWindow::getInstance().init(clientOutput);
	GameWindow::getInstance().startGameWindow(argc, argv);
}
