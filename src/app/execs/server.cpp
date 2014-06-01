#include "PoolingAcceptor.h"
#include "ProtobufConnection.h"
#include "IoHarbour.h"
#include "ConnectionPool.h"
#include "ConnectionBridge.h"
#include "ProtobufConnectionFactory.h"
#include "GameEngine.h"

#include "glog/logging.h"

using namespace ships;

int main(int argc, char * argv[]) {
	google::InitGoogleLogging(argv[0]);

	// Setup IoHarbour
	auto harbour = std::make_shared<IoHarbour>();

	// Setup PoolingAcceptor
	auto connectionFactory = std::make_shared<ProtobufConnectionFactory>(harbour);
	auto connectionPool = std::make_shared<ConnectionPool>();
	connectionPool->setConnsToSignal(2);
	auto acceptor = std::make_shared<PoolingAcceptor>(harbour, connectionPool, connectionFactory);

	//	Setup GameEngine and connect it to server
	auto gameEngine = std::make_shared<GameEngine>();
	auto bridge = std::make_shared<ConnectionBridge>(connectionPool, gameEngine);
	connectionPool->registerConnectionObserver(bridge);

	//	Run
	acceptor->listen("127.0.0.1", 8081);
	harbour->run();
	return 0;
}
