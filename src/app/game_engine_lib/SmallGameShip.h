/*
 * SmallGameShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef SMALLGAMESHIP_H_
#define SMALLGAMESHIP_H_

#include "GameShip.h"

class SmallGameShip: public GameShip {

public:
	SmallGameShip();
	virtual ~SmallGameShip() = default;
	using GameShip::ShipState;
	using GameShip::ShipPtr;

	static GameShip* createSmallGameShip(int);
	virtual ShipState getState() const override;
	virtual std::size_t getSize() const override;
	virtual void hit() override;

	virtual void addShip(ShipPtr ship) {};
	virtual void addShips(std::vector<ShipPtr> ships) {};
};

#endif /* SMALLGAMESHIP_H_ */
