/*
 * acceptor.h
 *
 *  created on: May 12, 2014
 *      author: Adam Kosiorek
 */

#ifndef aCCEPTOR_H_
#define aCCEPTOR_H_

#include <boost/asio.hpp>
#include <chrono>
#include <memory>

using namespace boost::asio;
using std::chrono::steady_clock;
using std::chrono::milliseconds;

namespace ships {

class IoHarbour;
class ProtobufConnection;

/**
 * An abstract Acceptor class. Adapted from:
 * http://www.gamedev.net/blog/950/entry-2249317-a-guide-to-getting-started-with-boostasio/?pg=10
 *
 * Member function description:
 * start*	initiates some event
 * dispatch*	schedules an asynchronous action
 * handle*	handles an event
 */
class Acceptor: public std::enable_shared_from_this<Acceptor> {
	friend class ioHarbour;
public:	//	Typedefs
	typedef std::shared_ptr<IoHarbour> HarbourPtr;

private:	//	 constructors
	Acceptor(const Acceptor& acceptor);
	Acceptor& operator =(const Acceptor& acceptor);

protected:	//	Constructors
	Acceptor(HarbourPtr harbour);
	virtual ~Acceptor() = default;

public:	//	Setters & getters
	std::shared_ptr<IoHarbour> getHarbour();
	ip::tcp::acceptor& getAcceptor();
	strand& getStrand();

	/**
	 * Sets timer interval in milliseconds. Default is 1000.
	 */
	void setTimerInterval(int32_t timerInterval);
	int32_t getTimerInterval() const;
	bool hasError();

public:	//	Methods
	/**
	 * Begin listening on the specific network interface.
	 */
	virtual void listen(const std::string& host, const uint16_t& port);

	/**
	 * Posts the connection to the listening interface. The next client that
	 * connections will be given this connection. if multiple calls to Accept
	 * are called at a time, then they are accepted in a fIFO order.
	 */
	virtual void accept(std::shared_ptr<ProtobufConnection> connection);

	/**
	 * Stop the Acceptor from listening.
	 */
	virtual void stop();

private:	//	Methods
	void startTimer();
	void startError(const boost::system::error_code& error);

	void dispatchAccept(std::shared_ptr<ProtobufConnection> connection);

	void handleTimer(const boost::system::error_code& error);
	void handleAccept(const boost::system::error_code& error,
			std::shared_ptr<ProtobufConnection> connection);
	bool handleError(const boost::system::error_code& error);

private:	//	Abstract methods
   /**
	* Called when a connection has connected to the server. This function
	* should return true to invoke the connection's onAccept function if the
	* connection will be kept. if the connection will not be kept, the
	* connection's disconnect function should be called and the function
	* should return false.
	*/
	virtual bool onAccept(std::shared_ptr<ProtobufConnection> connection,
			const std::string& host, uint16_t port) = 0;
   /**
	* Called on each timer event.
	*/
	virtual void onTimer(const milliseconds& delta) = 0;

   /**
	* Called when an error is encountered. Most typically, this is when the
	* acceptor is being closed via the stop function or if the Listen is
	* called on an address that is not available.
	*/
	virtual void onError(const boost::system::error_code& error) = 0;

private:	//	Fields
	HarbourPtr harbour_;
	ip::tcp::acceptor acceptor_;
	strand strand_;
	basic_waitable_timer<steady_clock> timer_;
	steady_clock::time_point lastTimerEvent_;
	int32_t timerInterval_;
	int error_;
};

} /* namespace ships */

#endif /* aCCEPTOR_H_ */
