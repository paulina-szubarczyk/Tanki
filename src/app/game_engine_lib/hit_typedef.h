/*
 * hit_typedef.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef HIT_TYPEDEF_H_
#define HIT_TYPEDEF_H_
#include "HitObserver.h"
#include <memory>
#include <boost/signals2/signal.hpp>

typedef boost::signals2::signal<void (void)> SignalHitType;
typedef void (*HitUpdateFun) (void);
typedef std::shared_ptr<HitObserver> HitObserverPtr;


#endif /* HIT_TYPEDEF_H_ */
