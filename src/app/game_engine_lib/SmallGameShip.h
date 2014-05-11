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

	virtual ShipState getState() const override;
	virtual std::size_t getSize() const override;

	virtual void hit() override;
};

#endif /* SMALLGAMESHIP_H_ */
