/*
 * ClientClientTcpConnection.h
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CLIENTClientTcpConnection_H_
#define CLIENTClientTcpConnection_H_

#include <iostream>
#include <array>

#include <google/protobuf/text_format.h>
#include <glog/logging.h>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/bind.hpp>

#include "tank.pb.h"
#include "packedmessage.h"

using boost::asio::ip::tcp;
namespace asio = boost::asio;

class ClientTcpConnection {
public:
	ClientTcpConnection(boost::asio::io_service &io);

	void start_read_header();

	void start_read_body(unsigned msgLen);

	void handle_read_header(const boost::system::error_code& error);

	void handle_read_body(const boost::system::error_code& error);

	// Called when enough data was read into m_readbuf for a complete request
	// message.
	// Parse the request, execute it and send back a response.
	//
	void handle_request();

private:
	tcp::socket socket_;
	tcp::acceptor acceptor_;
	data_buffer buffer_;

	const int HEADER_SIZE = 4;
	const bool DEBUG = true;
	PackedMessage<Tank> packedMsg_;
	typedef boost::shared_ptr<Tank> TankPointer;
};

#endif /* CLIENTClientTcpConnection_H_ */
