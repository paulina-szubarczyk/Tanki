/*
 * GamePlayer.h
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYER_H_
#define GAMEPLAYER_H_

#include "BigGameShip.h"
#include "FieldsUpdater.h"
#include "Gameboard.h"
#include "ProtobufConnection.h"
#include "MessageSender.h"
#include "MessageHandler.h"
#include "message.pb.h"

#include <vector>
class GamePlayer {
public:
	GamePlayer();
	virtual ~GamePlayer();

	friend class GamePlayerBuilder;

	void hitField(int x, int y);

private:
	std::vector<std::shared_ptr<BigGameShip>> ships_;
	std::shared_ptr<Gameboard> gameboard_;
	std::shared_ptr<FieldsUpdater> fieldsUpdater_;
	std::shared_ptr<ships::ProtobufConnection> connection_;
	std::shared_ptr<ships::MessageSender> msgSender_;
	std::shared_ptr<ships::MessageHandler<MessageType, DataMsg>> msgHandler_;
};

#endif /* GAMEPLAYER_H_ */
