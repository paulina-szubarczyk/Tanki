/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GamePlayerBuilder.h"
#include "Gameboard.h"
#include "Field.h"

GamePlayerBuilder::GamePlayerBuilder() : PlayerBuilder() {}

GamePlayerBuilder::~GamePlayerBuilder() {}

void GamePlayerBuilder::addPlayerGameboard(int size) {
	player_->gameboard_ = std::shared_ptr<Gameboard>(new Gameboard(size));
}
GamePlayer* GamePlayerBuilder::configPlayerFieldsUpdater(GamePlayer* firstPlayer, GamePlayer* secondPlayer) {
	firstPlayer->fieldsUpdater_= std::shared_ptr<FieldsUpdater> (new FieldsUpdater);

	auto shipsIter = secondPlayer->ships_.begin();
	auto shipsIterEnd = secondPlayer->ships_.end();
	while (shipsIterEnd != shipsIter)
		(*shipsIter)->registerShipObserver(firstPlayer->fieldsUpdater_);
}
void GamePlayerBuilder::addPlayerConnection(std::shared_ptr<ships::ProtobufConnection> connection) {
	player_->connection_ = connection;
}

void GamePlayerBuilder::addPlayerShips(std::vector<std::vector<int>> y,	std::vector<std::vector<int>> x) {
	auto xIter = x.begin();
	auto yIter = y.begin();
	while ( xIter != x.end() ) {
		addPlayerShip(*xIter,*yIter);
	}
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
