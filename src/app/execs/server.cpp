#include "PoolingAcceptor.h"
#include "ProtobufConnection.h"
#include "IoHarbour.h"
#include "MessagePacker.h"
#include "MessageHandler.h"
#include "ConnectionPool.h"
#include "ConnectionBridge.h"
#include "ProtobufConnectionFactory.h"
#include "GameEngine.h"
#include "message.pb.h"

#include "glog/logging.h"

using namespace ships;

int main(int argc, char * argv[]) {
	google::InitGoogleLogging(argv[0]);

	std::shared_ptr<IoHarbour> harbour(new IoHarbour());
	std::shared_ptr<ProtobufConnectionFactory> connectionFactory(new ProtobufConnectionFactory(harbour));

	std::shared_ptr<MessageHandler<MessageType, DataMsg>> msgHandler(new MessageHandler<MessageType, DataMsg>());
		msgHandler->setTypeMethod([](const DataMsg& msg) {return msg.type();});
		msgHandler->addMsgHandler(MessageType::LOGIN, [](const DataMsg& msg) {
			LOG(INFO) << "LOGIN: " << msg.login();
			LOG(INFO) << "PASSW: " << msg.password();
		});

	connectionFactory->setMsgHandler(msgHandler);

	std::shared_ptr<ConnectionPool> connectionPool(new ConnectionPool());

	std::shared_ptr<PoolingAcceptor> acceptor(new PoolingAcceptor(harbour, connectionPool, connectionFactory));
	acceptor->listen("127.0.0.1", 8080);

	harbour->run();
	std::shared_ptr<GameEngine> gameEngine(new GameEngine());
	std::shared_ptr<ConnectionBridge> bridge(new ConnectionBridge(connectionPool, gameEngine));
	connectionPool->registerConnectionObserver(bridge);
	return 0;
}
