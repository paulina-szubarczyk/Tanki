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

#include <thread>
#include <sstream>

#include <glog/logging.h>

using namespace ships;

int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);
	if(argc > 2) {
		std::stringstream sstream;
		sstream << "gui" << argv[2] << ".log";
		google::SetLogDestination(google::INFO, sstream.str().c_str());
	}


	std::shared_ptr<IoHarbour> harbour(new IoHarbour());
	std::thread thread([&]() {
		harbour->run();
	});

	auto msgHandler = std::make_shared<MessageHandler<MessageType, DataMsg>>();
	msgHandler->setTypeMethod([](const DataMsg& msg) -> MessageType {

		return msg.type();
	});

	std::shared_ptr<ProtobufConnection> connection = std::make_shared<ProtobufConnection>(harbour, msgHandler);

	std::shared_ptr<ClientOutput> clientOutput = std::make_shared<ClientOutput>(connection);
	std::shared_ptr<ClientInput> clientInput = std::make_shared<ClientInput>(clientOutput, msgHandler);

	GameWindow::getInstance().init(clientOutput);
	GameWindow::getInstance().startGameWindow(argc, argv);
}
