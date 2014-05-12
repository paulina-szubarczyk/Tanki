/*
 * ClientFieldUpdater.cpp
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#include "FieldsUpdater.h"

FieldsUpdater::FieldsUpdater() : ShipObserver() {
	// TODO Auto-generated constructor stub

}

FieldsUpdater::~FieldsUpdater() {
	// TODO Auto-generated destructor stub
}

void FieldsUpdater::shipHit() {

}

void FieldsUpdater::hit(FieldType field) {
//	secondPlayerGameboard_->hit(field);
	lastHit_ = field;
}

FieldsUpdater::FieldType FieldsUpdater::getLastHit() const{
	return lastHit_;
}
