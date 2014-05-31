/*
 * GameManager.h
 *
 *  Created on: May 30, 2014
 *      Author: klis
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "ClientConnection.h"
#include <memory>
#include <string>
#include <sstream>

class GameManager {

public:
	GameManager();
	void setShipsQuantity(std::map<int, int>& configuration);
	std::map<int, int>& getShipsQuantity();
	void setGridSize(int n);
	int getGridSize();
	void decreaseShipsQuantity(int shipSize);
	int getRemainingShips(int shipSize);
	int getSmallestSize();
	bool checkReady();

private:
	std::shared_ptr<ClientConnection> connector_;
	std::map<int, int> shipsQuantity_;
	std::map<int, int>::iterator iter_;
	int gridSize_;
};

#endif /* GAMEMANAGER_H_ */
