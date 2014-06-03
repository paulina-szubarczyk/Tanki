/*
 * IOutput.h
 *
 *  Created on: Jun 3, 2014
 *      Author: Adam Kosiorek
 */

#ifndef IOUTPUT_H_
#define IOUTPUT_H_

#include "ProtobufConnection.h"

#include "message.pb.h"

class IOutput {
protected:
	typedef std::shared_ptr<net::ProtobufConnection> ConnectionPtr;
	typedef std::shared_ptr<DataMsg> MsgPtr;
protected:
	IOutput(ConnectionPtr connection);
	virtual ~IOutput() = default;

	MsgPtr createMsg(MessageType type) const;
	void send(MsgPtr msg) const;
	ConnectionPtr connection_;
};

#endif /* IOUTPUT_H_ */
