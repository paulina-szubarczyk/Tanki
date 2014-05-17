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

void GameEngine::registerPlayer(ProtobufConnPtr connection_){

	if (!player1_) createPlayer(player1_, connection_);
	else if (!player2_) {
		createPlayer(player2_, connection_);
		startGame();
	}
	else {} // oba polaczenia zajete

}

void GameEngine::createGame(){
	GamePlayerBuilder::configPlayerFieldsUpdater(player1_,player2_);
	GamePlayerBuilder::configPlayerFieldsUpdater(player2_,player1_);
	// rozpocznij gre
}

void GameEngine::createPlayer(PlayerPtr player,ProtobufConnPtr connection_){

	GamePlayerBuilder playerBuilder(connection_);
	playerBuilder.createPlayer();
	player1_ = PlayerPtr(playerBuilder.getPlayer());

}

