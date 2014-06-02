/*
 * BigGameShip.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef BIGGAMESHIP_H_
#define BIGGAMESHIP_H_

#include "GameShip.h"
#include "HitObserver.h"
#include "ShipObserver.h"
#include <memory>
#include <boost/signals2/signal.hpp>
typedef boost::signals2::signal<void (GameShip::ShipState)> SignalShipType;
typedef std::shared_ptr<ShipObserver> ShipObserverPtr;

class BigGameShip: public GameShip {
	using GameShip::ShipState;
	using GameShip::ShipPtr;

public:
	BigGameShip();
	virtual ~BigGameShip() = default;

	SignalShipType hitShip;
	void registerShipObserver(ShipObserverPtr shipObserver);

	virtual void hit() override;

	static GameShip* createBigGameShip(int size);
	virtual ShipState getState() const override;
	virtual std::size_t getSize() const override;

	void addShip(ShipPtr ship);
	void addShips(std::vector<ShipPtr> ships);
	std::vector<ShipPtr> getShips();

private:
	std::vector<ShipPtr> ships_;
};

#endif /* BIGGAMESHIP_H_ */
