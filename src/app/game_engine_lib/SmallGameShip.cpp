/*
 * SmallGameShip.cpp
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#include "SmallGameShip.h"
#include "Field.h"
#include <iostream>

SmallGameShip::SmallGameShip() : field_(nullptr),GameShip(GameShip::ShipState::FLOAT){}
SmallGameShip::SmallGameShip(FieldPtr field): field_(field), GameShip(GameShip::ShipState::FLOAT){}

SmallGameShip::~SmallGameShip() {
	// TODO Auto-generated destructor stub
}

void SmallGameShip::changeState(FieldPtr field, ShipState state){
	if (field_ == field)
		this->state_ = state;
	else {
		std::cerr<<"[SmallGameShip.changeStateError] Param field doesn't belong to this ship.\n";
	}
}
GameShip::ShipState SmallGameShip::getState(){
	return state_;
}

std::size_t  SmallGameShip::getSize(){
	return 1;
}

void SmallGameShip::updateState(){}

void SmallGameShip::setField(FieldPtr field){
	if (field)
		field_ = field;
	else {
		std::cerr<<"[SmallGameShip.setFieldError] You are trying to set SmallGameShip on uninitialzed Field\n";
	}
}
SmallGameShip::FieldPtr SmallGameShip::getField(){
	return field_;
}
