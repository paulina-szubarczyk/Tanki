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
#include "IPlayerInput.h"
#include "IGameConfig.h"

#include <vector>
#include <memory>

namespace game {


typedef std::shared_ptr<GamePlayer> PlayerPtr;
typedef std::shared_ptr<IPlayerInput> InputPtr;

class GamesManager {
typedef std::shared_ptr<IGameConfig> GameConfigPtr;
public:
	GamesManager(GameConfigPtr gameConfig);
	virtual ~GamesManager() = default;

	void createGame(const std::vector<OutputPtr>& outputs, const std::vector<InputPtr>& inputs);

protected:
	std::vector<std::shared_ptr<Game>> games_;
	GameConfigPtr gameConfig_;

};

}

#endif /* GAMEENGIN_H_ */
