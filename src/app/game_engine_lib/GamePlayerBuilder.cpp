/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GamePlayerBuilder.h"

#include "glog/logging.h"

void GamePlayerBuilder::createGamePlayer(OutputPtr output) {
	LOG(INFO) << "Creating game player";
	createPlayer(output);
	//TODO size should be taken from a python configure script;
	int size = 10;
	addPlayerGameboard(size);
}
void GamePlayerBuilder::addPlayerGameboard(int size) {
	LOG(INFO) << "Adding gameboard";
	player_->getGameboard() = std::shared_ptr<Gameboard>(new Gameboard(size));
}

void  GamePlayerBuilder::configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2) {

	player1->setFieldsUpdater(std::shared_ptr<FieldsUpdater>
							(new FieldsUpdater(player1, player2)));

	auto shipsIter = player2->getShips().begin();
	auto shipsIterEnd = player2->ships_.end();
	while (shipsIterEnd != shipsIter)
		(*shipsIter)->registerShipObserver(player1->getFieldsUpdater());
}


void GamePlayerBuilder::addPlayerShips(std::vector<std::vector<int>> y,	std::vector<std::vector<int>> x) {
	auto xIter = x.begin();
	auto yIter = y.begin();
	while ( xIter != x.end() ) {
		addPlayerShip(*xIter,*yIter);
	}
	// check with rules if thats all ships, send info if not
}
void GamePlayerBuilder::addPlayerShip( std::vector<int> x, std::vector<int> y) {

	ShipPtr ship = ShipPtr(dynamic_cast<BigGameShip*>(shipFactory->creatShip("BigShip",x.size())));
	player_->ships_.push_back(ship);

	//Adding fieldObserver
	auto xIter = x.begin();
	auto yIter = y.begin();
	auto smallShipsIter = ship->getShips().begin();

	while ( xIter != x.end() ) {

		player_->getGameboard()->getField(*xIter,*yIter).registerHitObserver(ship);
		player_->getGameboard()->getField(*xIter,*yIter).registerHitObserver(*smallShipsIter);

		++xIter;
		++yIter;
		++smallShipsIter;
	}
}

