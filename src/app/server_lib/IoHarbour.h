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

class IoHarbour : public std::enable_shared_from_this<IoHarbour> {
public:
	IoHarbour();
	virtual ~IoHarbour();

	io_service& getService();
	bool hasStopped();
	void stop();
	void reset();
	void run();
	void poll();
	void dispatch(std::function<void()> fun);
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
