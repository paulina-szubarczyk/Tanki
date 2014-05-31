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
#include "MessagePacker.h"
#include "message.pb.h"

namespace ships {

/**
 * A concrete connection class. It handles Google Protocol Buffer-based connections.
 * Provides interface for sending protobuf message. Incoming message handling is done through
 * a message handling object. The on* methods have only a dummy implementation with logging.
 *
 * Uses a MessagePacker object to pack protobuf messsages.
 */
class ProtobufConnection: public Connection {
public:	//	Typedefs
	typedef MessagePacker<DataMsg> PackageType;
	typedef MessageHandler<MessageType, DataMsg> MsgHandlerType;
	typedef std::shared_ptr<MsgHandlerType> MsgHandlerPtr;

public:	//	Constructors
	ProtobufConnection(HarbourPtr harbour);
	ProtobufConnection(HarbourPtr harbour, MsgHandlerPtr msgHandler);
	~ProtobufConnection() = default;

public:	//	Methods

	/**
	 * Sends a DataMsg to the other side
	 */
	void send(std::shared_ptr<DataMsg> msg);
	MsgHandlerPtr getMsgHandler() const;
	void setMsgHandler(MsgHandlerPtr msgHandler);

	//	 Overriden abstract methods
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

	MessagePacker<DataMsg> msgPacker_;
	MsgHandlerPtr msgHandler_;
};

} /* namespace ships */

#endif /* SERVERCONNECTION_H_ */
