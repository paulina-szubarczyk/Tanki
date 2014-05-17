/*
 * ClientFieldUpdater.cpp
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#include "FieldsUpdater.h"

FieldsUpdater::FieldsUpdater(OutputPtr output1, OutputPtr output2, GameboardPtr gameboard) : ShipObserver(),
							playerOutput_(output1),oponentOutput_(output2), oponentGameboard_(gameboard) {}

FieldsUpdater::~FieldsUpdater() {}

void FieldsUpdater::shipHit(GameShip::ShipState state) {
	if (state == GameShip::ShipState::HIT)	{
		playerOutput_->oponentShipHit(lastHit_.first,lastHit_.second);
		oponentOutput_->playerShipHit(lastHit_.first,lastHit_.second);
	} else if (state == GameShip::ShipState::SUNK) {
		playerOutput_->oponentShipSunk(lastHit_.first,lastHit_.second);
		oponentOutput_->playerShipSunk(lastHit_.first,lastHit_.second);
	}
}

void FieldsUpdater::hit(int x, int y) {
	lastHit_ = std::make_pair(x,y);
	oponentGameboard_->hit(x,y);
}

FieldsUpdater::FieldType FieldsUpdater::getLastHit() const{
	return lastHit_;
}
