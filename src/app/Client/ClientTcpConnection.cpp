/*
 * ClientTcpConnection.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */

#include "ClientTcpConnection.h"

ClientTcpConnection::ClientTcpConnection(boost::asio::io_service &io) :
		socket_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 15)) {

	acceptor_.async_accept(socket_,
			boost::bind(&ClientTcpConnection::handle_read_header, this,
					boost::asio::placeholders::error));
}

void ClientTcpConnection::start_read_header() {
	buffer_.resize(HEADER_SIZE);
	asio::async_read(socket_, asio::buffer(buffer_),
			boost::bind(&ClientTcpConnection::handle_read_header, this,
					asio::placeholders::error));
}

void ClientTcpConnection::start_read_body(unsigned msgLen) {
	// m_readbuf already contains the header in its first HEADER_SIZE
	// bytes. Expand it to fit in the body as well, and start async
	// read into the body.
	//
	buffer_.resize(HEADER_SIZE + msgLen);
	asio::mutable_buffers_1 buf = asio::buffer(&buffer_[HEADER_SIZE], msgLen);
	asio::async_read(socket_, buf,
			boost::bind(&ClientTcpConnection::handle_read_body, this,
					asio::placeholders::error));
}

void ClientTcpConnection::handle_read_header(
		const boost::system::error_code& error) {

	DEBUG && (std::cerr << "handle read " << error.message() << '\n');
	if (!error) {
		DEBUG && (std::cerr << "Got header!\n");
		DEBUG && (std::cerr << show_hex(buffer_) << std::endl);
		unsigned msgLen = packedMsg_.decodeHeader(buffer_);
		DEBUG && (std::cerr << msgLen << " bytes\n");
		start_read_body(msgLen);
	}
}

void ClientTcpConnection::handle_read_body(
		const boost::system::error_code& error) {
	DEBUG && (std::cerr << "handle body " << error << '\n');
	if (!error) {
		DEBUG && (std::cerr << "Got body!\n");
		DEBUG && (std::cerr << show_hex(buffer_) << std::endl);
		handle_request();
	}
}

// Called when enough data was read into m_readbuf for a complete request
// message.
// Parse the request, execute it and send back a response.
//
void ClientTcpConnection::handle_request() {
	if (packedMsg_.unpack(buffer_)) {
		TankPointer tPtr = packedMsg_.getMsg();

		std::string textForm;
		google::protobuf::TextFormat::PrintToString(*tPtr, &textForm);
		std::cout << textForm << std::endl;
	}
}
