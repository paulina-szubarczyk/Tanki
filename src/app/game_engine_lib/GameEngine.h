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
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

	void registerPlayer(OutputPtr output);

	void createGame();
	void changeTurn();
	PlayerPtr getPlayer1();
	PlayerPtr getPlayer2();

protected:
	PlayerPtr player1_;
	PlayerPtr player2_;
	OutputPtr output1_;
	OutputPtr output2_;
	void createPlayer (PlayerPtr player, OutputPtr output);
	typedef boost::signals2::signal<void ()> StartGameType;
	StartGameType startGame;

};

#endif /* GAMEENGIN_H_ */
