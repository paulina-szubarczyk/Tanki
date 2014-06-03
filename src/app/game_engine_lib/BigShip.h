/*
 * BigGameShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef BIGGAMESHIP_H_
#define BIGGAMESHIP_H_

#include "IShip.h"
#include "HitObserver.h"
#include "ShipObserver.h"
#include <memory>
#include <boost/signals2/signal.hpp>

namespace game {
typedef boost::signals2::signal<void (IShip::ShipState)> SignalShipType;
typedef std::shared_ptr<ShipObserver> ShipObserverPtr;

class BigShip: public IShip {
	using IShip::ShipState;
	using IShip::ShipPtr;

public:
	BigShip();
	virtual ~BigShip() = default;

	SignalShipType hitShip;
	void registerShipObserver(ShipObserverPtr shipObserver);

	virtual void hit() override;

	static IShip* createBigGameShip(int size);
	virtual ShipState getState() const override;
	virtual std::size_t getSize() const override;

	void addShip(ShipPtr ship);
	void addShips(std::vector<ShipPtr> ships);
	std::vector<ShipPtr> getShips();

private:
	std::vector<ShipPtr> ships_;
};
}
#endif /* BIGGAMESHIP_H_ */
