/*
 * GamePlayerBuilder.h
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#ifndef PLAYERBUILDER_H_
#define PLAYERBUILDER_H_

#include "ShipFactoryMethod.h"
#include "GamePlayer.h"

class PlayerBuilder {
public:
	PlayerBuilder();
	virtual ~PlayerBuilder();

	typedef ships::MessageHandler<MessageType, DataMsg> MsgHandlerType;
	typedef std::shared_ptr<ships::MessageSender> MsgSenderPtr;
	typedef std::shared_ptr<ships::ProtobufConnection> ProtobufConnPtr;

	void createPlayer() {player_ = new GamePlayer();};
	GamePlayer* getPlayer() {return player_;};
	virtual void addPlayerGameboard(int size) = 0;
	virtual void addPlayerConnection( ProtobufConnPtr connection) = 0;
	virtual void addPlayerMsgHandler() = 0;
	virtual void addPlayerMsgSender() = 0;
	virtual void addPlayerShips(std::vector<std::vector<int>> y,
						std::vector<std::vector<int>> x) = 0;
	virtual void addPlayerShip( std::vector<int> x,
						std::vector<int> y) = 0;
//	virtual GamePlayer* configPlayerFieldsUpdater(GamePlayer*,GamePlayer*) = 0;

protected:
	GamePlayer* player_;
	ShipFactoryMethod* shipFactory;
	ProtobufConnPtr connection_;
	MsgSenderPtr msgSender_;
	std::shared_ptr<MsgHandlerType> msgHandler_;
};

#endif /* PLAYERBUILDER_H_ */
