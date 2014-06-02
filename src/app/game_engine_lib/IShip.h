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
namespace game {
class IShip: public HitObserver {
public:
	enum ShipState { FLOAT, SUNK, HIT };
	typedef std::shared_ptr<IShip> ShipPtr;

public:
	IShip() : state_(ShipState::FLOAT) {};
	virtual ~IShip() = default;

	virtual ShipState getState() const = 0;
	virtual std::size_t getSize() const = 0;

	virtual void addShip(ShipPtr ship) = 0;
	virtual void addShips(std::vector<ShipPtr> ships) = 0;

protected:
	ShipState state_;
};
}
#endif /* ABSTRACTSHIP_H_ */
