/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GamePlayerBuilder.h"

GamePlayerBuilder::GamePlayerBuilder() : PlayerBuilder() {

}

GamePlayerBuilder::~GamePlayerBuilder() {}

void GamePlayerBuilder::createGamePlayer(OutputPtr output) {
	createPlayer(output);
	//size from Rules;
	int size;
	addPlayerGameboard(size);
}
void GamePlayerBuilder::addPlayerGameboard(int size) {
	player_->gameboard_ = std::shared_ptr<Gameboard>(new Gameboard(size));
}

void  GamePlayerBuilder::configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2, OutputPtr output1, OutputPtr output2) {

	player1->fieldsUpdater_= std::shared_ptr<FieldsUpdater> (new FieldsUpdater(output1, output2, player2->gameboard_));

	auto shipsIter = player2->ships_.begin();
	auto shipsIterEnd = player2->ships_.end();
	while (shipsIterEnd != shipsIter)
		(*shipsIter)->registerShipObserver(player1->fieldsUpdater_);
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

		player_->gameboard_->getField(*xIter,*yIter).registerHitObserver(ship);
		player_->gameboard_->getField(*xIter,*yIter).registerHitObserver(*smallShipsIter);

		++xIter;
		++yIter;
		++smallShipsIter;
	}
}

