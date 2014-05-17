/*
 * ShipObserver.h
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#ifndef SHIPOBSERVER_H_
#define SHIPOBSERVER_H_
#include "GameShip.h"
class ShipObserver {
public:
	ShipObserver();
	virtual ~ShipObserver();

	virtual void shipHit(GameShip::ShipState state) = 0;
};

#endif /* SHIPOBSERVER_H_ */
