/*
 * GameEngin.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GamesManager.h"
#include "PlayerFactory.h"
#include "GamePlayer.h"
#include "IGameConfig.h"
#include "IPlayerOutput.h"

#include "glog/logging.h"


namespace game {

GamesManager::GamesManager(GameConfigPtr gameConfig) : gameConfig_(gameConfig) {};

void GamesManager::createGame(const std::vector<OutputPtr>& outputs, const std::vector<InputPtr>& inputs) {


	LOG(INFO) << "Creating a game";
	CHECK_EQ(outputs.size(), inputs.size()) << "Game requires 2 inputs and 2 outputs";
	CHECK_EQ(outputs.size(), 2) << "Game requires 2 inputs and 2 outputs";

	int gameboardSize = gameConfig_->getGameboardSize();
	std::map<int, int> shipConfig = gameConfig_->getShipConfig();

	auto outputIt = outputs.begin();
	auto inputIt = inputs.begin();
	std::vector<PlayerPtr> players;
	for(;outputIt != outputs.end(); ++inputIt, ++outputIt) {

		auto player = PlayerFactory::createGamePlayer(*outputIt, gameboardSize);

		(*outputIt)->setConfig(shipConfig, gameboardSize);

		(*inputIt)->setGamePlayer(player);
		(*inputIt)->registerAddShipMethod(PlayerFactory::addPlayerShips);
		players.push_back(player);
	}

	auto game = std::make_shared<Game>(players[0], players[1]);
	for(auto player : players) {
		player->setGame(game);
	}

	games_.push_back(game);
	LOG(INFO) << "Game created";
}
}


