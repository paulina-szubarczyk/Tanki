/*
 * BasicAcceptor.h
 *
 *  Created on: May 13, 2014
 *      Author: Adam Kosiorek
 */

#ifndef BASICACCEPTOR_H_
#define BASICACCEPTOR_H_

#include "Acceptor.h"

namespace ships {

class BasicAcceptor: public Acceptor {
public:
	BasicAcceptor(std::shared_ptr<ships::IoHarbour> harbour);
	~BasicAcceptor() = default;

private:
	bool onAccept(std::shared_ptr<ships::Connection> connection,
			const std::string & host, uint16_t port) override;
	void onTimer(const milliseconds& delta) override;
	void onError(const boost::system::error_code & error) override;
};

} /* namespace ships */

#endif /* BASICACCEPTOR_H_ */
