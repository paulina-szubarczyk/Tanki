/*
 * Connection.h
 *
 *  Created on: May 11, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <chrono>
#include <list>
#include <vector>

using namespace boost::asio;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

namespace ships {

class IoHarbour;
class Acceptior;

/**
 * Abstract Connection class. Adapted from:
 * http://www.gamedev.net/blog/950/entry-2249317-a-guide-to-getting-started-with-boostasio/?pg=10
 */
class Connection : public std::enable_shared_from_this<Connection> {
	friend class Acceptor;
public:	//	Typedefs
	typedef std::shared_ptr<IoHarbour> HarbourPtr;

public:	//	Constructors
	Connection(HarbourPtr harbour);
	virtual ~Connection() = default;

public:	//	Setters & Getters
	bool hasError() const;
	HarbourPtr getHarbour() const;
	int getReceiveBufferSize() const;
	void setReceiveBufferSize(int receiveBufferSize);
	const ip::tcp::socket& getSocket() const;
	ip::tcp::socket& getSocket();
	const strand& getStrand() const;
	strand& getStrand();
	int getTimerInterval() const;
	void setTimerInterval(int timerInterval);

public:	//	Methods
	// Binds the socket to the specified interface.
	virtual void bind(const std::string& ip, uint16_t port);

	// Starts an a/synchronous connect.
	virtual void connect(const std::string& host, uint16_t port);

	// Posts data to be sent to the connection.
	virtual void send(const std::vector<uint8_t>& buffer);

	// Posts a recv for the connection to process. If total_bytes is 0, then
	// as many bytes as possible up to GetReceiveBufferSize() will be
	// waited for. If Recv is not 0, then the connection will wait for exactly
	// total_bytes before invoking OnRecv.
	virtual void receive(int totalBytes = 0);

	// Posts an asynchronous disconnect event for the object to process.
	virtual void disconnect();

protected:	//	Methods
	void startSend();
	void startError(const boost::system::error_code & error);
	virtual void startReceive(int32_t totalBytes);
	void startTimer();

	void dispatchSend(std::vector<uint8_t> buffer);
	void dispatchReceive(int32_t totalBytes);
	void dispatchTimer(const boost::system::error_code& error);

	void handleConnect(const boost::system::error_code& error);
	bool handleError(const boost::system::error_code & error);
	void handleSend(const boost::system::error_code & error, std::list<std::vector<uint8_t> >::iterator it);
	void handleReceive(const boost::system::error_code & error, int actualBytes);
	void handleTimer(const boost::system::error_code& error);

protected:	//	Abstract methods
	// Called when the connection has successfully connected to the local
	// host.
	virtual void onAccept(const std::string& host, uint16_t port) = 0;

	// Called when the connection has successfully connected to the remote
	// host.
	virtual void onConnect(const std::string& host, uint16_t port) = 0;

	// Called when data has been sent by the connection.
	virtual void onSend(const std::vector<uint8_t>& buffer) = 0;

	// Called when data has been received by the connection.
	virtual void onReceive(std::vector<uint8_t>& buffer) = 0;

	// Called on each timer event.
	virtual void onTimer(const milliseconds& delta) = 0;

	// Called when an error is encountered.
	virtual void onError(const boost::system::error_code& error) = 0;


protected:	//	Fields
	HarbourPtr harbour_;
	ip::tcp::socket socket_;
	strand strand_;
	basic_waitable_timer<steady_clock> timer_;
	steady_clock::time_point lastTimerEvent_;
	int receiveBufferSize_;
	long timerInterval_;
	int error_;
	std::list<std::vector<uint8_t>> pendingSends_;
	std::list<int32_t> pendingReceives_;
	std::vector<uint8_t> receiveBuffer_;
};

} /* namespace ships */

#endif /* CONNECTION_H_ */
