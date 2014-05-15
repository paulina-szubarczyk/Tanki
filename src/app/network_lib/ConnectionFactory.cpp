/*
 * ConnectionFactory.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#include "ConnectionFactory.h"
#include "IoHarbour.h"

namespace ships {

auto ConnectionFactory::getHarbour() const -> HarbourPtr {
	return harbour_;
}

void ConnectionFactory::setHarbour(HarbourPtr harbour) {
	harbour_ = harbour;
}

ConnectionFactory::ConnectionFactory(HarbourPtr harbour) : harbour_(harbour) {};

}
