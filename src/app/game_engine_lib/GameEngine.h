/*
 * GameEngin.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEENGIN_H_
#define GAMEENGIN_H_
#include "GamePlayerBuilder.h"

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();
	typedef std::shared_ptr<ships::ProtobufConnection> ProtobufConnPtr;
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

	void registerPlayer(ProtobufConnPtr connection_);

	void createGame();

protected:
	PlayerPtr player1_;
	PlayerPtr player2_;
	void createPlayer (PlayerPtr player, ProtobufConnPtr connection_);
	typedef boost::signals2::signal<void ()> StartGameType;
	StartGameType startGame;

};

#endif /* GAMEENGIN_H_ */
