/*
 * session.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: Adam Kosiorek
 */

#include "session.h"

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {

}

void Session::start() {
	doRead();
}

void Session::doRead() {

	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_, max_length),
			[this, self](boost::system::error_code ec, std::size_t length){

		data.push_back(std::string(data_, 0, length));
//		sleep(1);
		std::cout.write(data_, length);
		std::cout << std::endl;
		if(!ec) doWrite(length);
	});
}

void Session::doWrite(std::size_t length) {

	auto self(shared_from_this());
	boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
			[this, self](boost::system::error_code ec, std::size_t) {

		if(!ec) doRead();
	});
}
