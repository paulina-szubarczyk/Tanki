/*
 * Game.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "Game.h"
#include "GameShip.h"
#include "GamePlayerBuilder.h"
#include "GamePlayer.h"

Game::Game(PlayerPtr player1, PlayerPtr player2) : player1_(player1), player2_(player2), prepared_(0) {}

void Game::initGame()
{
	GamePlayerBuilder::configPlayerFieldsUpdater(player1_,player2_);
	GamePlayerBuilder::configPlayerFieldsUpdater(player2_,player1_);


	player1_->getOutput()->beginGame();
	player2_->getOutput()->beginGame();

	player1_->setTurn(true);
	player2_->setTurn(false);
}

auto Game::getPlayer1() -> PlayerPtr {
	return player1_;
}

auto Game::getPlayer2() -> PlayerPtr {
	return player2_;
}

void Game::playerPrepared() {
    std::unique_lock<std::mutex> lock(player_);
    ++prepared_;
    if (prepared_ == 2)
    	initGame();
}

bool Game::isWinner(PlayerPtr player) {
	bool winner = true;
	for (auto ship = player->getShips().begin(); ship!=player->getShips().end(); ++ship)
		if (ship->get()->getState() != GameShip::ShipState::SUNK)
		{	winner = false;
			break;
		}
	if(winner) {
		if (player.get() == player1_.get()) {
			player1_->getOutput()->playerWin();
			player2_->getOutput()->oponentWin();
		} else {
			player2_->getOutput()->playerWin();
			player1_->getOutput()->oponentWin();
		}
		return true;
	}
	return false;
}
void Game::changeTurn() {
	if (player1_->isTurn()) {
		player1_->setTurn(false);
		player2_->setTurn(true);
	} else {
		player2_->setTurn(false);
		player1_->setTurn(true);
	}
}
