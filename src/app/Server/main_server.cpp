/*
 * main_server.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */

#include <iostream>
#include <memory>
#include <utility>

#include <boost/asio.hpp>

#include <google/protobuf/text_format.h>
#include "tank.pb.h"

#include "packedmessage.h"

#include "tcpserver.h"
#include "session.h"


int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    TcpServer s(io_service, std::atoi(argv[1]));

    io_service.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


//int main(int argc, char** argv) {

//	GOOGLE_PROTOBUF_VERIFY_VERSION;

//	std::cout << "Hello, World!" << std::endl;

//    // Initialize message
//	boost::shared_ptr<Message> mPtrOut(new Message());
//	mPtrOut->set_id("Adam");
//	mPtrOut->set_type(Message::B);

//    if(mPtrOut->IsInitialized())
//        std::cout << "messageOut is initialized" << std::endl;
//    else {
//        std::cout << "messageOut is not initialized" << std::endl;
//        return -1;
//    }

//    // print original message
//    std::string strOut;
//    google::protobuf::TextFormat::PrintToString(*mPtrOut, &strOut);
//    printf("%s\n%s\n", "Original message", strOut.c_str());

//    typedef std::vector<boost::uint8_t> data_buffer;
//    data_buffer buffer;

//    PackedMessage<Message> packedMessage(mPtrOut);
//    if(!packedMessage.pack(buffer)) {
//        std::cerr << "Couldn't pack message" << std::endl;
//        return -1;
//    }

//    boost::shared_ptr<Message> mPtrIn(new Message());
//    PackedMessage<Message> packedMessageIn(mPtrIn);
//    if(!packedMessageIn.unpack(buffer)) {
//        std::cerr << "Couldn't unpack message" << std::endl;
//        return -1;
//    }

//    std::string strIn;
//    google::protobuf::TextFormat::PrintToString(*mPtrIn, &strIn);
//    printf("%s\n%s\n", "Unpacked message", strOut.c_str());

//    std::cout << "a" << std::endl;
//    google::protobuf::ShutdownProtobufLibrary();
//	return 0;
//}

//int main() {
//	try {
//
//		boost::asio::io_service io_service;
//		TcpServer server(io_service);
//		io_service.run();
//	} catch (std::exception& e) {
//
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}
