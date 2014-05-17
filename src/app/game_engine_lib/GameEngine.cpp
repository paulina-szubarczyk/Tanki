/*
 * GameEngin.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GameEngine.h"
#include "GamePlayerBuilder.h"
#include <boost/signals2/signal.hpp>


GameEngine::GameEngine() {
	startGame.connect(boost::bind(&GameEngine::createGame,this));
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

void GameEngine::registerPlayer(OutputPtr output){

	if (!player1_)
		createPlayer(player1_, output);
	else if (!player2_) {
		createPlayer(player2_, output);
		startGame();
	}
	else {
		output->gameAlreadyOccupied();
	}
}

void GameEngine::createGame(){
	GamePlayerBuilder::configPlayerFieldsUpdater(player1_,player2_,output1_,output2_);
	GamePlayerBuilder::configPlayerFieldsUpdater(player2_,player1_,output2_,output1_);
	output1_->beginGame();
	output2_->beginGame();

	player1_->changeTurn(true);
	player2_->changeTurn(false);
}

void GameEngine::createPlayer(PlayerPtr player, OutputPtr output){

	GamePlayerBuilder playerBuilder;
	playerBuilder.createGamePlayer(output);
	player1_ = PlayerPtr(playerBuilder.getPlayer());

}

GameEngine::PlayerPtr GameEngine::getPlayer1(){
	return player1_;
}
GameEngine::PlayerPtr GameEngine::getPlayer2(){
	return player2_;
}

