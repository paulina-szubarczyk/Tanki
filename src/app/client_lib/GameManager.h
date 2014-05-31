/*
 * GameManager.h
 *
 *  Created on: May 30, 2014
 *      Author: klis
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <map>
#include <string>
#include <sstream>

class GameManager{

public:
	GameManager();
	void setShipsQuantity(std::map<int,int>& configuration);
	void updateShipsToAdd(std::string shipsToAdd);
	std::map<int,int>& getShipsQuantity();
	void setGridSize(int n);
	int getGridSize();
	int getTypesNumber();
	void setTurn();
	void setWait();
	//std::string getShipsToAdd();


private:
	std::map<int,int> shipsQuantity_;
	//std::string shipsToAdd_;
	int gridSize_;
};


#endif /* GAMEMANAGER_H_ */
