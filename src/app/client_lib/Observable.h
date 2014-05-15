/*
 * observable.h
 *
 *  Created on: May 11, 2014
 *      Author: klis
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <list>
class Observer;

/*
 * Observable object interface *
 */
class Observable{
public:
	virtual ~Observable();
	virtual void attachObserver(Observer* observer); //allaws to attach a new observer to the observable object
	virtual void detachObserver(Observer* observer); //allows to detach an already attached observer from the object
	virtual void notify(); //notifies all attached obesrvers about a change in the state of the object
protected:
	Observable();

	std::list <Observer*> observers_; //list containing attached observers
};



#endif /* OBSERVABLE_H_ */
