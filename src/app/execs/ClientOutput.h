/*
 * ClientOutput.h
 *
 *  Created on: Jun 1, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CLIENTOUTPUT_H_
#define CLIENTOUTPUT_H_

#include "ClientConnection.h"
#include "ProtobufConnection.h"
#include "message.pb.h"

namespace ships {

class ClientOutput: public ClientConnection {
	typedef std::shared_ptr<ProtobufConnection> ConnectionPtr;
	typedef std::shared_ptr<DataMsg> MsgPtr;

public:
	ClientOutput(ConnectionPtr connection);
	virtual ~ClientOutput() = default;

	virtual void connect(std::string serverIP, unsigned short port);
	virtual void sendShip(std::vector<std::vector<std::pair<int,int>>> shipVec);
	virtual void sendHit(std::pair<int,int> hitCoordinates);

private:
	MsgPtr createMsg(MessageType type) const;
	void send(MsgPtr msg) const;
	ConnectionPtr connection_;
};

} /* namespace ships */

#endif /* CLIENTOUTPUT_H_ */
