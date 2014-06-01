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

namespace ships {
	class PlayerInput;
}

using namespace ships;

typedef std::shared_ptr<PlayerInput> InputPtr;

class GameEngine {
	typedef std::shared_ptr<GamePlayer> PlayerPtr;
public:
	GameEngine() = default;
	virtual ~GameEngine() = default;

	void createGame(OutputPtr output1, InputPtr input1, OutputPtr output2, InputPtr input2);

protected:
	std::vector<std::shared_ptr<Game>> games_;

};

#endif /* GAMEENGIN_H_ */
