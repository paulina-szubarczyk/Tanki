/*
 * GameEngin.cpp
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#include "GameEngine.h"
#include "GamePlayerBuilder.h"
#include "PlayerInput.h"
#include "GamePlayer.h"

#include "glog/logging.h"


void GameEngine::createGame(OutputPtr output1, InputPtr input1, OutputPtr output2, InputPtr input2) {

	LOG(INFO) << "Creating a game";

	PlayerPtr player1 = GamePlayerBuilder::createGamePlayer(output1);
	PlayerPtr player2 = GamePlayerBuilder::createGamePlayer(output2);

	LOG(ERROR) << 1;
	input1->setGamePlayer(player1);
	LOG(ERROR) << 2;
	input1->registerAddShipMethod(player1, GamePlayerBuilder::addPlayerShips);

	LOG(ERROR) << 3;
	input2->setGamePlayer(player2);
	LOG(ERROR) << 4;
	input2->registerAddShipMethod(player2, GamePlayerBuilder::addPlayerShips);
	LOG(ERROR) << 5;

	auto game = std::make_shared<Game>(player1, player2);

	player1->setGame(game);
	player2->setGame(game);

	games_.push_back(game);
	LOG(INFO) << "Game created";
}


