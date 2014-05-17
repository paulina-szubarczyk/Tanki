/*
 * MessageSender.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef MESSAGESENDER_H_
#define MESSAGESENDER_H_

#include "ProtobufConnection.h"
#include "message.pb.h"
#include <memory>

namespace ships {

/**
 * Prepares and sends protobuf DataMsg messages
 */
class MessageSender {
public:
	typedef std::shared_ptr<ProtobufConnection> ConnectionPtr;
	typedef std::shared_ptr<DataMsg> MsgPtr;
public:
	MessageSender(ConnectionPtr connection);
	virtual ~MessageSender() = default;

	/**
	 * Sends a message that the owner of the connection was hit and the coordinates of the ship hit
	 */
	void sendHitThisXY(int x, int y);

	/**
	 * Sends a message that the opponent of the owner of the connection was hit and the coordinates of the ship hit
	 */
	void sendHitThatXY(int x, int y);

	/**
	 * Sends a message that the owner of the connection have won
	 */
	void sendWin();

	/**
	 * Sends a message that the owner of the connection have lost
	 */
	void sendLose();

	/**
	 * Sends a message that the opponent has left
	 */
	void sendOtherPlayerLeft();

	/**
	 * Sends a message that the game has ended
	 */
	void sendGameOver();

	void sendGetShips();

	ConnectionPtr getConnection() const;
	void setConnection(ConnectionPtr connection);

private:
	MsgPtr createMsg() const;
	ConnectionPtr connection_;
};

} /* namespace ships */

#endif /* MESSAGESENDER_H_ */
