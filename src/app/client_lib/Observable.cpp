/*
 * observable.cpp
 *
 *  Created on: May 11, 2014
 *      Author: klis
 */

#include "Observable.h"
#include "Observer.h"

void Observable::attachObserver(Observer* observer){
	observers_.push_back(observer);
}

void Observable::detachObserver(Observer* observer){
	observers_.remove(observer);
}

void Observable::notify(){
	std::list<Observer*>::iterator it;
	for(it = observers_.begin(); it != observers_.end(); it++){
		(*it)->update(this);
	}
}

