/*
 * HittenObserver.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef HITTENOBSERVER_H_
#define HITTENOBSERVER_H_

#include <memory>
#include <boost/signals2/signal.hpp>

namespace game {
class HitObserver;
	typedef boost::signals2::signal<void (void)> SignalHitType;
	typedef std::shared_ptr<HitObserver> HitObserverPtr;

class HitObserver {
public:
	HitObserver() = default;
	virtual ~HitObserver() = default;

	virtual void hit() = 0;
};
}
#endif /* HITTENOBSERVER_H_ */
