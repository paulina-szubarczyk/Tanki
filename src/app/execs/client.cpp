#include "ProtobufConnection.h"
#include "IoHarbour.h"
#include "MessagePacker.h"
#include "MessageHandler.h"

#include "message.pb.h"

#include "glog/logging.h"

#include <thread>
#include <mutex>
#include <iostream>
#include <iomanip>

using namespace ships;

int main(int argc, char * argv[]) {
	google::InitGoogleLogging(argv[0]);

	std::shared_ptr<ships::IoHarbour> harbour(new ships::IoHarbour());

	std::shared_ptr<MessageHandler<MessageType, DataMsg>> msgHandler(new MessageHandler<MessageType, DataMsg>());
	msgHandler->setTypeMethod([](const DataMsg& msg) {return msg.type();});
	msgHandler->addMsgHandler(MessageType::LOGIN, [](const DataMsg& msg) {
		LOG(INFO) << "LOGIN: " << msg.login();
		LOG(INFO) << "PASSW: " << msg.password();
	});

	std::shared_ptr<ProtobufConnection> connection(new ProtobufConnection(harbour, msgHandler));
	connection->connect("127.0.0.1", 7777);

	std::shared_ptr<DataMsg> dataMsg(new DataMsg());
	dataMsg->set_type(MessageType::LOGIN);
	dataMsg->set_login("adam");
	dataMsg->set_password("passwd");

	while(true) {
		connection->send(dataMsg);
		harbour->poll();
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	return 0;
}
