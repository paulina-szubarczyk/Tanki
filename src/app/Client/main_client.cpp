/*
 * 	main_client.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */

#include <iostream>
#include <array>
#include <boost/asio.hpp>
#include<thread>
#include <google/protobuf/text_format.h>
#include <glog/logging.h>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/bind.hpp>

#include "packedmessage.h"

#include "ClientTcpConnection.h"

using boost::asio::ip::tcp;
namespace asio = boost::asio;

int main(int argc, char** argv) {

	google::InitGoogleLogging(argv[0]);


    LOG(INFO) << "Starting!";

		try {
		std::string server = "localhost";
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server, "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		std::string str = "query";
		str += argv[1];

		std::thread thread([&]() {
			while(true) {
			socket.write_some(boost::asio::buffer(str));
			std::cout << "aha!\n";
			}
		});


			while(true) {
				std::array<char, 128> buf;
				boost::system::error_code error;
				size_t len = socket.read_some(boost::asio::buffer(buf), error);
				if(error == boost::asio::error::eof)
					break;
				else if(error)
					throw boost::system::system_error(error);

				std::cout.write(buf.data(), len);
				std::cout << std::endl;
			}

			thread.join();


	} catch (std::exception &e) {

		std::cerr << e.what() << std::endl;
	}
}