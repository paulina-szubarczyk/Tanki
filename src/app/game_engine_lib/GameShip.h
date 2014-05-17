/*
 * GameShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef ABSTRACTSHIP_H_
#define ABSTRACTSHIP_H_

#include <memory>
#include <vector>
#include "HitObserver.h"

class GameShip: public HitObserver {
public:
	enum ShipState { FLOAT, SUNK, HIT };
	typedef std::shared_ptr<GameShip> ShipPtr;

	GameShip();
	virtual ~GameShip() = default;

	static  GameShip* createGameShip() {};
	virtual ShipState getState() const {} ;
	virtual std::size_t getSize() const {};
	virtual void hit() override;

	virtual void addShip(ShipPtr ship) {};
	virtual void addShips(std::vector<ShipPtr> ships) {};

protected:
	ShipState state_;
};
#endif /* ABSTRACTSHIP_H_ */
