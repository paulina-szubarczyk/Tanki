/*
 * GameEngin.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GameEngine.h"
#include "GamePlayerBuilder.h"

#include "glog/logging.h"


void GameEngine::createGame(OutputPtr output1, OutputPtr output2){

	LOG(INFO) << "Creating a game";

	PlayerPtr player1_, player2_;
	createPlayer(player1_, output1);
	createPlayer(player2_, output2);
	auto game = std::make_shared<Game>(player1_,player2_);
	player1_->setGame(game);
	player2_->setGame(game);
	games_.push_back(game);
	LOG(INFO) << "Game created";
}


void GameEngine::createPlayer(PlayerPtr player, OutputPtr output){

	LOG(INFO) << "Creating a player";
	GamePlayerBuilder playerBuilder;
	playerBuilder.createGamePlayer(output);
	*player = *PlayerPtr(playerBuilder.getPlayer());

}


