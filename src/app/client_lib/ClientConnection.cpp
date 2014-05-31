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


