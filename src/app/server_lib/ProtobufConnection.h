/*
 * ServerConnection.h
 *
 *  Created on: May 13, 2014
 *      Author: Adam Kosiorek
 */

#ifndef SERVERCONNECTION_H_
#define SERVERCONNECTION_H_

#include "Connection.h"

#include "MessageHandler.h"
#include "PackedMessage.h"
#include "message.pb.h"

namespace ships {

class ProtobufConnection: public Connection {
public:	//	Typedefs
	typedef PackedMessage<DataMsg> PackageType;
	typedef MessageHandler<MessageType, DataMsg> MsgHandlerType;
	typedef std::shared_ptr<MsgHandlerType> MsgHandlerPtr;

public:	//	Constructors
	ProtobufConnection(HarbourPtr harbour, MsgHandlerPtr msgHandler);
	~ProtobufConnection() = default;

public:	//	Methods
	void send(std::shared_ptr<DataMsg> msg);

private:	//	 Overriden abstract methods
	void onAccept(const std::string & host, uint16_t port) override;
	void onConnect(const std::string & host, uint16_t port) override;;
	void onSend(const std::vector<uint8_t> & buffer) override;;
	void onReceive(std::vector<uint8_t> & buffer) override;;
	void onTimer(const milliseconds& delta) override;;
	void onError(const boost::system::error_code & error) override;;

private:	//	Methods
	virtual void startReceive(int32_t totalBytes = 0) override; //header
	void startReceiveBody(int32_t totalBytes); //header

	void handleReceiveHeader(const boost::system::error_code & error);
	void handleReceiveBody(const boost::system::error_code & error);

	PackedMessage<DataMsg> packedMessage;
	MsgHandlerPtr msgHandler_;
};

} /* namespace ships */

#endif /* SERVERCONNECTION_H_ */
