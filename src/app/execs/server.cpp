#include "PoolingAcceptor.h"
#include "ProtobufConnection.h"
#include "IoHarbour.h"
#include "ConnectionPool.h"
#include "ConnectionBridge.h"
#include "ProtobufConnectionFactory.h"
#include "GamesManager.h"
#include "MessageHandler.h"
#include "IGameConfig.h"
#include "PyGameConfig.h"
#include "ShipFactoryMethod.h"
#include "SmallShip.h"
#include "BigShip.h"

#include "message.pb.h"
#include "glog/logging.h"

#include <thread>

using namespace net;
using namespace game;

int main(int argc, char * argv[]) {
	google::InitGoogleLogging(argv[0]);
	google::SetLogDestination(google::INFO, "server.log");

	if (argc < 4) {
		LOG(FATAL)<< "Arguments: <ip> <port> <configure_script>";
	}

	std::string ipAddr(argv[1]);
	int port = std::stoi(argv[2]);
	std::string gameConfigScript(argv[3]);

	// Setup IoHarbour
	auto harbour = std::make_shared<IoHarbour>();

	// Setup PoolingAcceptor
	//	Setup MessageHandler
	auto msgHandler = std::make_shared<MessageHandler<MessageType, DataMsg>>();
	msgHandler->setTypeMethod([](const DataMsg& msg) -> MessageType {

		return msg.type();
	});

	//	Setup ConnectionFactory
	auto connectionFactory = std::make_shared<ProtobufConnectionFactory>(
			harbour);
	connectionFactory->setMsgHandler(msgHandler);

	auto connectionPool = std::make_shared<ConnectionPool>();
	connectionPool->setConnsToSignal(2);
	auto acceptor = std::make_shared<PoolingAcceptor>(harbour, connectionPool,
			connectionFactory);

	//	Setup ShipFactoryMethod
	ShipFactoryMethod::getInstance()->registerShip("BigShip",BigShip::createBigGameShip);
	ShipFactoryMethod::getInstance()->registerShip("SmallShip", SmallShip::createSmallGameShip);

	//	Setup GamesManager and connect it to server
	std::shared_ptr<IGameConfig> gameConfig = std::make_shared<PyGameConfig>(
			gameConfigScript);
	auto gameEngine = std::make_shared<game::GamesManager>(gameConfig);
	auto bridge = std::make_shared<ConnectionBridge>(connectionPool,
			gameEngine);
	connectionPool->registerConnectionObserver(bridge);

	//	Run
	acceptor->listen(ipAddr, port);
	std::thread thread([&]() {harbour->run();});

	std::shared_ptr<ProtobufConnection> connection1 = std::make_shared<
			ProtobufConnection>(harbour);
	std::shared_ptr<ProtobufConnection> connection2 = std::make_shared<
			ProtobufConnection>(harbour);

//	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	connection1->connect("127.0.0.1", port);
	connection2->connect("127.0.0.1", port);

	thread.join();
	return 0;
}
