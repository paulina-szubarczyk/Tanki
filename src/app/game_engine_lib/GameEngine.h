/*
 * GameEngin.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEENGIN_H_
#define GAMEENGIN_H_
#include "GamePlayerBuilder.h"
#include "Game.h"

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();
	typedef std::shared_ptr<GamePlayer> PlayerPtr;
	void createGame(OutputPtr output1, OutputPtr output2);

protected:
	void createPlayer (PlayerPtr player, OutputPtr output);
	std::vector<std::shared_ptr<Game>> games_;

};

#endif /* GAMEENGIN_H_ */
