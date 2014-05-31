/*
 * PlayerOutput.cpp
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#include "PlayerOutput.h"

PlayerOutput::PlayerOutput(std::shared_ptr<ships::Connection> connection) {
}

PlayerOutput::~PlayerOutput() {
}

void PlayerOutput::getShips() {
}

void PlayerOutput::beginGame() {
}

void PlayerOutput::playerTurn() {
}

void PlayerOutput::playerShipHit(int x, int y) {
}

void PlayerOutput::playerShipSunk(int x, int y) {
}

void PlayerOutput::oponentShipHit(int x, int y) {
}

void PlayerOutput::oponentShipSunk(int x, int y) {
}

void PlayerOutput::oponentWin() {
}

void PlayerOutput::playerWin() {
}

void PlayerOutput::gameAlreadyOccupied() {
}

void PlayerOutput::notEnoughShips(int delivered, int expected) {
}

void PlayerOutput::playerNotReady() {
}

void PlayerOutput::oponentNotReady() {
}



void PlayerOutput::oponentTurn() {
}
