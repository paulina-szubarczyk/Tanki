/*
 * ConnectionObserver.h
 *
 *  Created on: May 15, 2014
 *      Author: Adam Kosiorek
 */

#ifndef CONNECTIONOBSERVER_H_
#define CONNECTIONOBSERVER_H_

namespace ships {

/**
 * Connection Observer interface. Should be implemented by any class observing a Connection Pool.
 */
struct ConnectionObserver {

	virtual ~ConnectionObserver() = default;
	virtual void signal() = 0;
};

}



#endif /* CONNECTIONOBSERVER_H_ */
