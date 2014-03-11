/*
 * TcpServer.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */
#include "tcpserver.h"

#include "session.h"

TcpServer::TcpServer(boost::asio::io_service &io_service, short port) :
	acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
	socket_(io_service) {

	doAccept();
}


void TcpServer::doAccept() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {

		if(!ec) std::make_shared<Session>(std::move(socket_))->start();

		doAccept();
	});
}
