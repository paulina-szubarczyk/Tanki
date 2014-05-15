/*
 * IoHarbour.h
 *
 *  Created on: May 11, 2014
 *      Author: Adam Kosiorek
 */

#ifndef IOHARBOUR_H_
#define IOHARBOUR_H_

#include <boost/asio.hpp>

#include <functional>
#include <memory>

using namespace boost::asio;

namespace ships {

/**
 * boost::asio::io_service wrapper class. Adapted from:
 * http://www.gamedev.net/blog/950/entry-2249317-a-guide-to-getting-started-with-boostasio/?pg=10
 */
class IoHarbour : public std::enable_shared_from_this<IoHarbour> {
public:
	IoHarbour();
	virtual ~IoHarbour();

	io_service& getService();
	bool hasStopped();

	/**
	 *	Stops harbour from execution.
	 */
	void stop();

	/**
	 *	Resets a harbour. Required after called stop().
	 */
	void reset();

	/**
	 *	Runs harbour until it is stopped. Do not call in single threaded applications.
	 */
	void run();

	/**
	 *	Polls harbour and executes all there is on an execution queue. Call in single
	 *	threaded applications
	 */
	void poll();

	/**
	 *	Dispatches a functor for asynchronous execution. Faster than post, but never executed immediately.
	 */
	void dispatch(std::function<void()> fun);

	/**
	 *	Posts a functor for asynchronous execution. Executes immediately if possible.
	 */
	void post(std::function<void()> fun);

private:
	IoHarbour(const IoHarbour&);
	IoHarbour& operator=(const IoHarbour&);

	typedef std::shared_ptr<io_service::work> WorkPtr;

	io_service ioService_;
	WorkPtr work_;
};

} /* namespace ships */

#endif /* IOHARBOUR_H_ */
