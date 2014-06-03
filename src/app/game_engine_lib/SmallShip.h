/*
 * SmallShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef SMALLGAMESHIP_H_
#define SMALLGAMESHIP_H_

#include "IShip.h"
namespace game {
class SmallShip: public IShip {

public:
	SmallShip();
	virtual ~SmallShip() = default;
	using IShip::ShipState;
	using IShip::ShipPtr;

	static IShip* createSmallGameShip(int);
	virtual ShipState getState() const override;
	virtual std::size_t getSize() const override;
	virtual void hit() override;

	virtual void addShip(ShipPtr ship) {};
	virtual void addShips(std::vector<ShipPtr> ships) {};
};
}
#endif /* SMALLGAMESHIP_H_ */
