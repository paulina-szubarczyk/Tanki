/*
 * GameManager.cpp
 *
 *  Created on: May 30, 2014
 *      Author: klis
 */

#include "GameManager.h"

GameManager::GameManager(){
/*
 * Testing values
 */
	gridSize_=10;
	shipsQuantity_.insert(std::pair<int,int>(5,1));
	shipsQuantity_.insert(std::pair<int,int>(2,3));
	shipsQuantity_.insert(std::pair<int,int>(3,2));
//	setGridSize(connector_->getGridSize());
//	setShipsQuantity(connector_->getShipsConfig());
}

bool GameManager::checkReady(){
	for(iter_ = shipsQuantity_.begin(); iter_ != shipsQuantity_.end();++iter_)
		if(iter_->second != 0)
			return false;
	return true;
}
std::map<int,int>& GameManager::getShipsQuantity(){
	return shipsQuantity_;
}

int GameManager::getSmallestSize(){
	iter_=shipsQuantity_.begin();
	return iter_->first;
}

void GameManager::decreaseShipsQuantity(int shipSize){
	iter_ = shipsQuantity_.find(shipSize);
	(iter_->second)--;
}

int GameManager::getRemainingShips(int shipSize){
	iter_ = shipsQuantity_.find(shipSize);
	return iter_->second;
}

void GameManager::setGridSize(int n){
	gridSize_ = n;
}

void GameManager::setShipsQuantity(std::map<int,int>& configuration){
	shipsQuantity_ = configuration;
}
