/*
 * PlayerFactory.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "PlayerFactory.h"
#include "BigShip.h"
#include "Gameboard.h"
#include "GamePlayer.h"
#include "ShipFactoryMethod.h"
#include "IPlayerOutput.h"

#include "glog/logging.h"

namespace game {

auto PlayerFactory::createGamePlayer(OutputPtr output, int gameboardSize) -> PlayerPtr {

	LOG(INFO) << "Creating game player";;
	auto player = std::make_shared<GamePlayer>(output);

	LOG(INFO) << "Adding gameboard";
	player->setGameboard(std::make_shared<Gameboard>(gameboardSize));

	return player;
}

void  PlayerFactory::configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2) {

	player1->setFieldsUpdater(std::shared_ptr<FieldsUpdater>
							(new FieldsUpdater(player1, player2)));

	auto shipsIter = player2->getShips().begin();
	auto shipsIterEnd = player2->ships_.end();
	while (shipsIterEnd != shipsIter)
		(*shipsIter)->registerShipObserver(player1->getFieldsUpdater());
}


void PlayerFactory::addPlayerShips(PlayerPtr player, std::vector<std::vector<int>> y,	std::vector<std::vector<int>> x) {
	auto xIter = x.begin();
	auto yIter = y.begin();
	while ( xIter != x.end() ) {
		addPlayerShip(player, *xIter++,*yIter++);
	}
	// check with rules if thats all ships, send info if not
}
void PlayerFactory::addPlayerShip(PlayerPtr player, std::vector<int> x, std::vector<int> y) {

	ShipPtr ship = ShipPtr(dynamic_cast<BigShip*>(ShipFactoryMethod::getInstance()->creatShip("BigShip",x.size())));
	player->ships_.push_back(ship);

	//Adding fieldObserver
	auto xIter = x.begin();
	auto yIter = y.begin();
	auto smallShipsIter = ship->getShips().begin();

	while ( xIter != x.end() ) {

		player->getGameboard()->getField(*xIter,*yIter).registerHitObserver(ship);
		player->getGameboard()->getField(*xIter,*yIter).registerHitObserver(*smallShipsIter);

		++xIter;
		++yIter;
		++smallShipsIter;
	}
}
}

