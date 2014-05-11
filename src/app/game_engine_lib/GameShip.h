/*
 * GameShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef ABSTRACTSHIP_H_
#define ABSTRACTSHIP_H_

#include <memory>
#include "HitObserver.h"

class GameShip: public HitObserver {
public:
	enum ShipState { FLOAT, SUNK, HIT };

	GameShip();
	GameShip(ShipState state);
	virtual ~GameShip() = default;

	virtual ShipState getState() const {} ;
	virtual std::size_t getSize() const {};
	virtual void hit() override;

protected:
	ShipState state_;
};
#endif /* ABSTRACTSHIP_H_ */
