#include "BasicAcceptor.h"
#include "ProtobufConnection.h"
#include "IoHarbour.h"
#include "MessagePacker.h"
#include "MessageHandler.h"

#include "message.pb.h"

#include "glog/logging.h"

using namespace ships;

int main(int argc, char * argv[]) {
	google::InitGoogleLogging(argv[0]);

	std::shared_ptr<IoHarbour> harbour(new IoHarbour());

	std::shared_ptr<BasicAcceptor> acceptor(new BasicAcceptor(harbour));
	acceptor->listen("127.0.0.1", 7777);

	std::shared_ptr<MessageHandler<MessageType, DataMsg>> msgHandler(new MessageHandler<MessageType, DataMsg>());
	msgHandler->setTypeMethod([](const DataMsg& msg) {return msg.type();});
	msgHandler->addMsgHandler(MessageType::LOGIN, [](const DataMsg& msg) {
		LOG(INFO) << "LOGIN: " << msg.login();
		LOG(INFO) << "PASSW: " << msg.password();
	});

	std::shared_ptr<ProtobufConnection> connection(new ProtobufConnection(harbour, msgHandler));
	acceptor->accept(connection);

	harbour->run();

	return 0;
}
