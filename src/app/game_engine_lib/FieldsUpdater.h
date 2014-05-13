/*
 * ClientFieldUpdater.h
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#ifndef CLIENTFIELDUPDATER_H_
#define CLIENTFIELDUPDATER_H_

#include "ShipObserver.h"
#include <utility>
#include <memory>
#include "Gameboard.h"

class FieldsUpdater: public ShipObserver {
public:
	FieldsUpdater();
	FieldsUpdater(std::shared_ptr<Gameboard> gameboard);
	virtual ~FieldsUpdater();

	virtual void shipHit() override;

	typedef std::pair<int,int> FieldType;


	void hit(FieldType field);
	FieldType getLastHit() const;

private:
	FieldType lastHit_;
	std::shared_ptr<Gameboard> secondPlayerGameboard_;
};

#endif /* CLIENTFIELDUPDATER_H_ */
