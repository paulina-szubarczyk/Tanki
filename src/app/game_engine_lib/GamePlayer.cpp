/*
 * GamePlayer.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "GamePlayer.h"
#include "Game.h"

GamePlayer::GamePlayer(OutputPtr output) : output_(output), turn_(false), hit_(false) {
	// TODO Auto-generated constructor stub

}


GamePlayer::~GamePlayer() {
	// TODO Auto-generated destructor stub
}

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
