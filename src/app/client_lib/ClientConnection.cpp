/*
 * ClientConnection.cpp
 *
 *  Created on: May 31, 2014
 *      Author: klis
 */
#include "ClientConnection.h"
#include "GameWindow.h"

void ClientConnection::setGridSize(int n){
	GameWindow::getInstance().getManager().setGridSize(n);
}

void ClientConnection::setShipsConfig(std::map<int,int>& config){
	GameWindow::getInstance().getManager().setShipsQuantity(config);
}

void ClientConnection::setHitReply(int x, int y, bool result){
	GameWindow::getInstance().setHitResult(x,y,result);
}

void ClientConnection::setShipsConfig(std::map<int,int>& config){
	GameWindow::getInstance().getManager().setShipsQuantity(config);
}

void ClientConnection::setHitReply(int x, int y, bool result){
	GameWindow::getInstance().setHitResult(x,y,result);
}

void ClientConnection::setTurn(bool turn){
	GameWindow::getInstance().setPlayerTurn(turn);
}
