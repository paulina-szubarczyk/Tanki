/*
 * ShipObserver.h
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#ifndef SHIPOBSERVER_H_
#define SHIPOBSERVER_H_

#include "IShip.h"
#include <memory>
#include <boost/signals2/signal.hpp>
namespace game {
class ShipObserver;
typedef boost::signals2::signal<void (IShip::ShipState)> SignalShipType;
typedef std::shared_ptr<ShipObserver> ShipObserverPtr;

class ShipObserver {
public:
	ShipObserver() = default;
	virtual ~ShipObserver() = default;

	virtual void shipHit(IShip::ShipState state) = 0;
};
}

#endif /* SHIPOBSERVER_H_ */
