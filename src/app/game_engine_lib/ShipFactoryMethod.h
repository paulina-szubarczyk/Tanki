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
#include "IShip.h"
namespace game {
class ShipFactoryMethod {
public:
	virtual ~ShipFactoryMethod();

	typedef IShip* (*CreateShipFun) (int size);

	static ShipFactoryMethod* getInstance(void);
	void registerShip(std::string shipName, CreateShipFun createShip);
	IShip* creatShip(std::string shipName, int shipSize);
private:

	ShipFactoryMethod();
	ShipFactoryMethod(const	ShipFactoryMethod&);
	static ShipFactoryMethod* instance_;
	std::map<std::string, CreateShipFun> creator_;
};
}
#endif /* SHIPFACTORYMETHOD_H_ */
