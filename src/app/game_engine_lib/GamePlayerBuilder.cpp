/*
 * GamePlayerBuilder.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GamePlayerBuilder.h"

GamePlayerBuilder::GamePlayerBuilder(ProtobufConnPtr connection) : PlayerBuilder() {
	connection_ = connection;
}

GamePlayerBuilder::~GamePlayerBuilder() {}

void GamePlayerBuilder::createGamePlayer() {
	createPlayer();
	addPlayerConnection(connection_);
	addPlayerMsgSender();
	addPlayerMsgHandler();
	//size from Rules;
	int size;
	addPlayerGameboard(size);
	shipsError_ = true;
	msgSender_->sendGetShips();
	// msgHandler funkcja odbierająca statki
	while (!shipsError_);
	// GameEngin dodaje FieldsUpdater;
}
void GamePlayerBuilder::addPlayerGameboard(int size) {
	player_->gameboard_ = std::shared_ptr<Gameboard>(new Gameboard(size));
}
void  GamePlayerBuilder::configPlayerFieldsUpdater(PlayerPtr firstPlayer, PlayerPtr secondPlayer) {
	firstPlayer->fieldsUpdater_= std::shared_ptr<FieldsUpdater> (new FieldsUpdater);

	auto shipsIter = secondPlayer->ships_.begin();
	auto shipsIterEnd = secondPlayer->ships_.end();
	while (shipsIterEnd != shipsIter)
		(*shipsIter)->registerShipObserver(firstPlayer->fieldsUpdater_);
}
void GamePlayerBuilder::addPlayerConnection(ProtobufConnPtr connection) {
	player_->connection_ = connection;
}

void GamePlayerBuilder::addPlayerShips(std::vector<std::vector<int>> y,	std::vector<std::vector<int>> x) {
	auto xIter = x.begin();
	auto yIter = y.begin();
	while ( xIter != x.end() ) {
		addPlayerShip(*xIter,*yIter);
	}
	// check with rules if thats all ships, send info if not
	shipsError_ = false;
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

void GamePlayerBuilder::addPlayerMsgHandler() {
	MsgHandlerType m;
	//TODO register function
}

void GamePlayerBuilder::addPlayerMsgSender() {
	player_->msgSender_ = msgSender_;
}
