/*
 * observer.h
 *
 *  Created on: May 11, 2014
 *      Author: klis
 */

/* Observer interface, the pointer to the observable object which called observer is passed
 * as update function's argument
 */
#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "Observable.h"

class Observer {
public:
	virtual ~Observer();
	virtual void update(Observable* observable) = 0;
protected:
	Observer();
};



#endif /* OBSERVER_H_ */
