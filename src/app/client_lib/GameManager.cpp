/*
 * GameManager.cpp
 *
 *  Created on: May 30, 2014
 *      Author: klis
 */

#include "GameManager.h"

void GameManager::updateShipsToAdd(){

	shipsToAdd_.clear();
	//shipsToAdd_+="S|Q\n";

	std::map<int,int>::iterator it;
	for(it = shipsQuantity_.begin();it != shipsQuantity_.end(); ++it){
		shipsToAdd_+= static_cast<std::ostringstream*>( &(std::ostringstream() << it->first) )->str();
		shipsToAdd_+= ' ';
		shipsToAdd_+= static_cast<std::ostringstream*>( &(std::ostringstream() << it->second) )->str();
		shipsToAdd_+= '\n';



	}
}

std::map<int,int>& GameManager::getShipsQuantity(){
	return shipsQuantity_;
}

std::string GameManager::getShipsToAdd(){
	return shipsToAdd_;
}
