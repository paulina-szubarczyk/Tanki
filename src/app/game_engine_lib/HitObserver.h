/*
 * HittenObserver.h
 *
 *  Created on: May 11, 2014
 *      Author: paulina
 */

#ifndef HITTENOBSERVER_H_
#define HITTENOBSERVER_H_

class HitObserver {
public:
	HitObserver();
	virtual void hit() = 0;
	virtual ~HitObserver() = default;
};

#endif /* HITTENOBSERVER_H_ */
