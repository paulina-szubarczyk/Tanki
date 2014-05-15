/*
 * ProtobufConnectionFactory.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef PROTOBUFCONNECTIONFACTORY_H_
#define PROTOBUFCONNECTIONFACTORY_H_

#include "ConnectionFactory.h"
#include "MessageHandler.h"

#include "message.pb.h"

namespace ships {

/**
 * ProtobufConnection object factory. It inject IoHarbour and, if provided,
 * a MessageHandler object to the connections it creates.
 */
class ProtobufConnectionFactory: public ConnectionFactory {
public:	//	Typedefs
	typedef std::shared_ptr<MessageHandler<MessageType, DataMsg>> MsgHandlerPtr;
public:
	ProtobufConnectionFactory(HarbourPtr harbour);
	virtual ~ProtobufConnectionFactory() = default;

	virtual ConnectionPtr createConnection() const override;

	MsgHandlerPtr getMsgHandler() const;
	void setMsgHandler(MsgHandlerPtr msgHandler);

private:
	MsgHandlerPtr msgHandler_;

};

} /* namespace ships */

#endif /* PROTOBUFCONNECTIONFACTORY_H_ */
