/*
 * hit_typedef.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef HIT_TYPEDEF_H_
#define HIT_TYPEDEF_H_
#include "ShipObserver.h"
#include <memory>
#include <boost/signals2/signal.hpp>

typedef boost::signals2::signal<void (void)> SignalShipType;
typedef std::shared_ptr<ShipObserver> ShipObserverPtr;


#endif /* HIT_TYPEDEF_H_ */
