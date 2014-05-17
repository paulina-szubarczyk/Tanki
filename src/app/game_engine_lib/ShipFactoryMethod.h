/*
 * ShipFactoryMethod.h
 *
 *  Created on: May 14, 2014
 *      Author: paulina
 */

#ifndef SHIPFACTORYMETHOD_H_
#define SHIPFACTORYMETHOD_H_
#include <map>
#include <memory>
#include "GameShip.h"

class ShipFactoryMethod {
public:
	virtual ~ShipFactoryMethod();

	typedef GameShip* (*CreateShipFun) (int size);

	static ShipFactoryMethod* getInstance(void);
	void registerShip(std::string shipName, CreateShipFun createShip);
	GameShip* creatShip(std::string shipName, int shipSize);
private:

	ShipFactoryMethod();
	ShipFactoryMethod(const	ShipFactoryMethod&);
	static ShipFactoryMethod* instance_;
	std::map<std::string, CreateShipFun> creator_;
};

#endif /* SHIPFACTORYMETHOD_H_ */
