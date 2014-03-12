/*
 * TcpServer.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: Adam Kosiorek
 */
#include "tcpserver.h"



TcpServer::TcpServer(boost::asio::io_service &io_service, short port) :
	acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
	socket_(io_service),
	connectionCounter_(0) {

	doAccept();
}

void TcpServer::doAccept() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {

//		if(!ec) std::make_shared<Session>(std::move(socket_))->start();
		if(!ec) {

			auto session = std::make_shared<Session>(std::move(socket_));
			connections_.insert(std::make_pair(connectionCounter_++, session));
			session->start();

		}

		doAccept();
	});
}

void TcpServer::printDetails() {

	for(auto elem : connections_) {

		std::cout << elem.first << "\t";
		for(auto str : elem.second->data)
			std::cout << str << " ";
		std::cout << std::endl;

	}
}
