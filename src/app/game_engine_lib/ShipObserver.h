/*
 * ShipObserver.h
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#ifndef SHIPOBSERVER_H_
#define SHIPOBSERVER_H_

class ShipObserver {
public:
	ShipObserver();
	virtual ~ShipObserver();

	virtual void shipHit() = 0;
};

#endif /* SHIPOBSERVER_H_ */
