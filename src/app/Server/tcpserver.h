/*
 * TcpServer.h
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <memory>
#include <utility>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace asio = boost::asio;

class TcpServer {
public:
	TcpServer(boost::asio::io_service &io_service, short port);

private:
	void doAccept();

	tcp::acceptor acceptor_;
	tcp::socket socket_;
};

#endif // TCPSERVER_H
