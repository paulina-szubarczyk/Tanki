/*
 * GameEngin.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEENGIN_H_
#define GAMEENGIN_H_

#include "PlayerFactory.h"
#include "Game.h"

#include <vector>

namespace ships {
	class PlayerInput;
}

using namespace ships;



namespace game {
	typedef std::shared_ptr<GamePlayer> PlayerPtr;
	typedef std::shared_ptr<PlayerInput> InputPtr;

class GamesManager {

public:
	GamesManager() = default;
	virtual ~GamesManager() = default;

	void createGame(const std::vector<OutputPtr>& outputs, const std::vector<InputPtr>& inputs);

protected:
	std::vector<std::shared_ptr<Game>> games_;

};
}

#endif /* GAMEENGIN_H_ */
