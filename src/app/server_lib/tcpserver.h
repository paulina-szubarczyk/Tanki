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
#include <map>

#include <boost/asio.hpp>

#include "session.h"

using boost::asio::ip::tcp;
namespace asio = boost::asio;

class TcpServer {
public:
	TcpServer(boost::asio::io_service &io_service, short port);


	void printDetails();
private:
	void doAccept();

	tcp::acceptor acceptor_;
	tcp::socket socket_;
	std::map<int, std::shared_ptr<Session>> connections_;
	int connectionCounter_;
};

#endif // TCPSERVER_H
