/*
 * Field.h
 *
 *  Created on: May 10, 2014
 *      Author: paulina
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "HitObserver.h"
#include <memory>
#include <boost/signals2/signal.hpp>
namespace game {
typedef boost::signals2::signal<void (void)> SignalHitType;
typedef std::shared_ptr<HitObserver> HitObserverPtr;

class SmallShip;
class Field {
public:
	Field();
	Field(int position);
	Field(const Field &field);
	~Field();

	int getPosition() const ;

	SignalHitType hit;
	void registerHitObserver(HitObserverPtr hitObserver);

private:
	int position_;
};

inline bool operator<(const Field &f1, const Field &f2){
	return f1.getPosition() < f2.getPosition();
}
}

#endif /* FIELD_H_ */
