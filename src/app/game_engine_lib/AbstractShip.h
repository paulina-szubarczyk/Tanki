/*
 * AbstractShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef ABSTRACTSHIP_H_
#define ABSTRACTSHIP_H_
#include "Field.h"

class AbstractShip {
public:
	AbstractShip();
	virtual ~AbstractShip();

	enum class ShipState { FLOAT, SUNK, HIT };

	virtual void changeState(Field* field, ShipState state) = 0;
	ShipState getState() { return state_;}

protected:
	virtual void updateState();
	ShipState state_;
};

#endif /* ABSTRACTSHIP_H_ */
