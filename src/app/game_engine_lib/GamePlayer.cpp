/*
 * GamePlayer.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "GamePlayer.h"
#include "Game.h"
#include "IPlayerOutput.h"
#include "Gameboard.h"
#include "BigShip.h"
#include "FieldsUpdater.h"
#include "Game.h"

namespace game {

GamePlayer::GamePlayer(OutputPtr output) : output_(output), turn_(false), hit_(false) {}

void GamePlayer::hitField(int x, int y) {
	if (turn_){
		hit_ = false;
		fieldsUpdater_->hit(x,y);
		if (!hit_){
			fieldsUpdater_->shipsNotHit(x,y);
			game_->changeTurn();
		}
	}
	else
		output_->oponentTurn();
}

void GamePlayer::shipsAdded() {
	game_->playerPrepared();
}

void GamePlayer::setTurn(bool turn) {
	turn_ = turn;
	if (turn_) output_->playerTurn();
}

auto GamePlayer::getOutput() const -> OutputPtr {
	return output_;
}

auto GamePlayer::getFieldsUpdater() -> FieldsUpdaterPtr {
	return fieldsUpdater_;
}

void GamePlayer::setFieldsUpdater(const FieldsUpdaterPtr& fieldsUpdater) {
	fieldsUpdater_ = fieldsUpdater;
}

std::vector<std::shared_ptr<BigShip> >& GamePlayer::getShips()  {
	return ships_;
}

void GamePlayer::setShips(const std::vector<std::shared_ptr<BigShip> >& ships) {
	ships_ = ships;
}

auto GamePlayer::getGameboard() const -> GameboardPtr {
	return gameboard_;
}

void GamePlayer::setGameboard(GameboardPtr gameboard) {
		gameboard_ = gameboard;;
}

bool GamePlayer::isTurn() const {
	return turn_;
}

std::shared_ptr<Game> GamePlayer::getGame() const {
	return game_;
}

void GamePlayer::setGame(std::shared_ptr<Game> game) {
	game_ = game;
}

bool GamePlayer::isHit() const {
	return hit_;
}

void GamePlayer::setHit(bool hit) {
	hit_ = hit;
}
}
