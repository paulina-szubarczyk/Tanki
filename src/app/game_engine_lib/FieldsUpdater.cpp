/*
 * ClientFieldUpdater.cpp
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#include "FieldsUpdater.h"

FieldsUpdater::FieldsUpdater() : ShipObserver() {}

FieldsUpdater::FieldsUpdater(std::shared_ptr<Gameboard> gameboard ) : ShipObserver(), secondPlayerGameboard_(gameboard){}

FieldsUpdater::~FieldsUpdater() {}

void FieldsUpdater::shipHit() {

}

void FieldsUpdater::hit(FieldType field) {
	secondPlayerGameboard_->hit(field);
	lastHit_ = field;
}

FieldsUpdater::FieldType FieldsUpdater::getLastHit() const{
	return lastHit_;
}
