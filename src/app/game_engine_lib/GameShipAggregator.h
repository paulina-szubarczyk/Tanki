/*
 * GameShipAggregator.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef GAMESHIPAGGREGATOR_H_
#define GAMESHIPAGGREGATOR_H_

#include "AbstractShip.h"
#include <map>

class GameShipAggregator: public AbstractShip {
public:
	GameShipAggregator();
	virtual ~GameShipAggregator();

	size_t getSize();
	void setGameShips(std::map<Field,GameShip> ships);
	void changeState(Field field, ShipState state);

private:
	std::map<Field,GameShip> ships_;
	void updateState();
};

#endif /* GAMESHIPAGGREGATOR_H_ */
