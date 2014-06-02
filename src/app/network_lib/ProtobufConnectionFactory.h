/*
 * ProtobufConnectionFactory.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PROTOBUFCONNECTIONFACTORY_H_
#define PROTOBUFCONNECTIONFACTORY_H_

#include "MessageHandler.h"

#include "message.pb.h"

namespace ships {

class IoHarbour;
class ProtobufConnection;

/**
 * ProtobufConnection object factory. It inject IoHarbour and, if provided,
 * a MessageHandler object to the connections it creates.
 */
class ProtobufConnectionFactory {
public:	//	Typedefs
	typedef MessageHandler<MessageType, DataMsg> MsgHandlerType;
	typedef std::shared_ptr<MsgHandlerType> MsgHandlerPtr;
	typedef std::shared_ptr<ProtobufConnection> ConnectionPtr;
	typedef std::shared_ptr<IoHarbour> HarbourPtr;
public:
	ProtobufConnectionFactory(HarbourPtr harbour);
	virtual ~ProtobufConnectionFactory() = default;

	virtual ConnectionPtr createConnection() const;

	MsgHandlerPtr getMsgHandler() const;
	void setMsgHandler(MsgHandlerPtr msgHandler);

	HarbourPtr getHarbour() const;
	void setHarbour(HarbourPtr harbour);

private:
	MsgHandlerPtr msgHandler_;
	HarbourPtr harbour_;

};

} /* namespace ships */

#endif /* PROTOBUFCONNECTIONFACTORY_H_ */
