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
#include "gameEngine_typedef.h"

class FieldsUpdater: public ShipObserver {
public:
	FieldsUpdater(OutputPtr output1, OutputPtr output2, GameboardPtr gameboard);
	FieldsUpdater();
	virtual ~FieldsUpdater();

	virtual void shipHit(GameShip::ShipState state) override;

	typedef std::pair<int,int> FieldType;


	void hit(int x, int y);
	FieldType getLastHit() const;

private:
	FieldType lastHit_;
	GameboardPtr oponentGameboard_;
	OutputPtr oponentOutput_;
	OutputPtr playerOutput_;
};

#endif /* CLIENTFIELDUPDATER_H_ */
