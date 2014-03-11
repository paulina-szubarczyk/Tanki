/*
 * Session.h
 *
 *  Created on: Mar 10, 2014
 *      Author: adam
 */

#ifndef SESSION_H_
#define SESSION_H_

#include <iostream>
#include <memory>
#include <utility>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace asio = boost::asio;

class Session : public std::enable_shared_from_this<Session> {
public:
	Session(tcp::socket socket);
	void start();

private:
	void doRead();
	void doWrite(std::size_t length);

	tcp::socket socket_;
	enum {max_length = 1024};
	char data_[max_length];
};



#endif /* SESSION_H_ */
