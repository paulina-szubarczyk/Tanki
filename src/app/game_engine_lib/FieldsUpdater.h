/*
 * ClientFieldUpdater.h
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#ifndef CLIENTFIELDUPDATER_H_
#define CLIENTFIELDUPDATER_H_

#include "ShipObserver.h"
#include <array>
#include <memory>

class FieldsUpdater: public ShipObserver {
public:
	FieldsUpdater();
	virtual ~FieldsUpdater();

	virtual void shipHit() override;

	typedef std::array<int,2> FieldType;

	void hit(FieldType field);
	FieldType getLastHit() const;

private:
	FieldType lastHit_;
};

#endif /* CLIENTFIELDUPDATER_H_ */
