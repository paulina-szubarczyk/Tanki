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
	using GameShip::FieldPtr;
public:
	SmallGameShip();
	SmallGameShip(FieldPtr field);
	virtual ~SmallGameShip();

	virtual void changeState(FieldPtr field, ShipState state) override;
	virtual ShipState getState();
	virtual std::size_t getSize();

	void setField(FieldPtr field);
	FieldPtr getField();
protected:
	virtual void updateState();
	GameShip::FieldPtr field_;
};

#endif /* SMALLGAMESHIP_H_ */
