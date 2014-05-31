/*
 * GameEngin.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GameEngine.h"
#include "GamePlayerBuilder.h"

GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}



void GameEngine::createGame(OutputPtr output1, OutputPtr output2){
	PlayerPtr player1_, player2_;
	createPlayer(player1_, output1);
	createPlayer(player2_, output2);
	std::shared_ptr<Game> game( new Game(player1_,player2_));
	player1_->setGame(game); player2_->setGame(game);
	games_.push_back(game);
}


void GameEngine::createPlayer(PlayerPtr player, OutputPtr output){

	GamePlayerBuilder playerBuilder;
	playerBuilder.createGamePlayer(output);
	player = PlayerPtr(playerBuilder.getPlayer());

}


