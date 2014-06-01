/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GamePlayerBuilder.h"
#include "BigGameShip.h"
#include "Gameboard.h"
#include "GamePlayer.h"
#include "ShipFactoryMethod.h"

#include "glog/logging.h"

auto GamePlayerBuilder::createGamePlayer(OutputPtr output) -> PlayerPtr {

	LOG(INFO) << "Creating game player";;
	auto player = std::make_shared<GamePlayer>(output);

	//TODO size should be taken from a python configure script;
	int size = 10;
	addPlayerGameboard(player, size);

	return player;
}
void GamePlayerBuilder::addPlayerGameboard(PlayerPtr player, int size) {
	LOG(INFO) << "Adding gameboard";
	player->setGameboard(std::make_shared<Gameboard>(size));
}

void  GamePlayerBuilder::configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2) {

	player1->setFieldsUpdater(std::shared_ptr<FieldsUpdater>
							(new FieldsUpdater(player1, player2)));

	auto shipsIter = player2->getShips().begin();
	auto shipsIterEnd = player2->ships_.end();
	while (shipsIterEnd != shipsIter)
		(*shipsIter)->registerShipObserver(player1->getFieldsUpdater());
}


void GamePlayerBuilder::addPlayerShips(PlayerPtr player, std::vector<std::vector<int>> y,	std::vector<std::vector<int>> x) {
	auto xIter = x.begin();
	auto yIter = y.begin();
	while ( xIter != x.end() ) {
		addPlayerShip(player, *xIter++,*yIter++);
	}
	// check with rules if thats all ships, send info if not
}
void GamePlayerBuilder::addPlayerShip(PlayerPtr player, std::vector<int> x, std::vector<int> y) {

	ShipPtr ship = ShipPtr(dynamic_cast<BigGameShip*>(ShipFactoryMethod::getInstance()->creatShip("BigShip",x.size())));
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

