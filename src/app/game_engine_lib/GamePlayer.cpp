/*
 * GamePlayer.cpp
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#include "GamePlayer.h"

GamePlayer::GamePlayer(OutputPtr output) : output_(output), turn_(false) {
	// TODO Auto-generated constructor stub

}

GamePlayer::~GamePlayer() {
	// TODO Auto-generated destructor stub
}

void GamePlayer::changeTurn(bool turn){
	turn_ = turn;
}

bool GamePlayer::getTurn(){
	return turn_;
}
void GamePlayer::hitField(int x, int y) {
	if (turn_)
		fieldsUpdater_->hit(x,y);
	else
		output_->oponentTurn();
}

GameboardPtr GamePlayer::getGameboard() {
	return gameboard_;
}
