/*
 * ConnectionFactory.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CONNECTIONFACTORY_H_
#define CONNECTIONFACTORY_H_

#include <memory>

namespace ships {

class ProtobufConnection;
class IoHarbour;

/**
 * Connection Factory interface. Prepares Connection objects;
 */
class ConnectionFactory {
public:	//	Typedefs
	typedef std::shared_ptr<ProtobufConnection> ConnectionPtr;
	typedef std::shared_ptr<IoHarbour> HarbourPtr;
public:
	ConnectionFactory(HarbourPtr harbour);
	virtual ~ConnectionFactory() = default;

	virtual ConnectionPtr createConnection() const = 0;

	HarbourPtr getHarbour() const;
	void setHarbour(HarbourPtr harbour);

protected:
	HarbourPtr harbour_;
};

} /* namespace ships */

#endif /* CONNECTIONFACTORY_H_ */
