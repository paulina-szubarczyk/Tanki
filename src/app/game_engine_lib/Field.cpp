/*
 * Field.cpp
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#include "Field.h"
#include "SmallGameShip.h"

Field::Field():position_(0) {}
Field::Field(int position):position_(position) {}
Field::~Field() {}
Field::Field(const Field &field) : Field(field.position_) {}

int Field::getPosition() const  {
	return position_;
}

void Field::registerHitObserver(HitObserverPtr hitObserver){
	hit.connect(SignalHitType::slot_type( &HitObserver::hit, hitObserver.get()).track_foreign(hitObserver));
}
