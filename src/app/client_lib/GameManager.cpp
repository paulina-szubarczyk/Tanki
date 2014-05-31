/*
 * GameManager.cpp
 *
 *  Created on: May 30, 2014
 *      Author: klis
 */

#include "GameManager.h"

GameManager::GameManager(){
	//shipsToAdd_ = "Waiting for configuration";
	gridSize_=10;
	shipsQuantity_.insert(std::pair<int,int>(1,1));
	shipsQuantity_.insert(std::pair<int,int>(2,2));
}
void GameManager::updateShipsToAdd(std::string shipsToAdd){

	shipsToAdd.clear();
	//shipsToAdd_+="S|Q\n";

	std::map<int,int>::iterator it;
	for(it = shipsQuantity_.begin();it != shipsQuantity_.end(); ++it){
		shipsToAdd+= static_cast<std::ostringstream*>( &(std::ostringstream() << it->first) )->str();
		shipsToAdd+= '|';
		shipsToAdd+= static_cast<std::ostringstream*>( &(std::ostringstream() << it->second) )->str();
		shipsToAdd+= '\n';



	}
}

std::map<int,int>& GameManager::getShipsQuantity(){
	return shipsQuantity_;
}

int GameManager::getTypesNumber(){
	return shipsQuantity_.size();
}
//std::string GameManager::getShipsToAdd(){
//	return shipsToAdd_;
//}
