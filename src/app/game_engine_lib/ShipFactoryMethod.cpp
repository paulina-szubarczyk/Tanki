/*
 * ShipFactoryMethod.cpp
 *
 *  Created on: May 14, 2014
 *      Author: paulina
 */

#include "ShipFactoryMethod.h"
namespace game {
ShipFactoryMethod* ShipFactoryMethod::instance_ = nullptr;
ShipFactoryMethod::ShipFactoryMethod() {
}

ShipFactoryMethod::~ShipFactoryMethod() {}

ShipFactoryMethod*  ShipFactoryMethod::getInstance(void) {
	if(!instance_)
		instance_ = new ShipFactoryMethod();
	return instance_;
}

void ShipFactoryMethod::registerShip(std::string shipName, CreateShipFun createShip){
	creator_[shipName] = createShip;
}
IShip* ShipFactoryMethod::creatShip(std::string shipName, int shipSize){
	return creator_[shipName](shipSize);
}
}
