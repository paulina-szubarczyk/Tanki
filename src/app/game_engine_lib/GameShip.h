/*
 * GameShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef ABSTRACTSHIP_H_
#define ABSTRACTSHIP_H_

#include <memory>

class Field;

class GameShip {
public:
	typedef std::shared_ptr<Field> FieldPtr;
	enum class ShipState { FLOAT, SUNK, HIT };

	GameShip();
	GameShip(ShipState state);
	virtual ~GameShip();

	virtual void changeState(FieldPtr field, ShipState state) = 0;
	virtual ShipState getState() = 0;
	virtual std::size_t getSize() = 0;
protected:
	virtual void updateState() = 0;
	ShipState state_;
};
#endif /* ABSTRACTSHIP_H_ */
