/*
 * ClientFieldUpdater.cpp
 *
 *  Created on: May 12, 2014
 *      Author: paulina
 */

#include "FieldsUpdater.h"
#include "GamePlayer.h"

FieldsUpdater::FieldsUpdater(PlayerPtr player1, PlayerPtr player2) : ShipObserver(),
							player_(player1),oponent_(player2) {}

FieldsUpdater::~FieldsUpdater() {}

void FieldsUpdater::shipHit(GameShip::ShipState state) {
	if (state == GameShip::ShipState::HIT)	{
		player_->setHit(true);
		player_->getOutput()->oponentShipHit(lastHit_.first,lastHit_.second);
		oponent_->getOutput()->playerShipHit(lastHit_.first,lastHit_.second);
	} else if (state == GameShip::ShipState::SUNK) {
		player_->setHit(true);
		player_->getOutput()->oponentShipSunk(lastHit_.first,lastHit_.second);
		oponent_->getOutput()->playerShipSunk(lastHit_.first,lastHit_.second);
		if (player_->getGame()->isWinner(player_))
			return;
	}
	player_->getGame()->changeTurn();
}

void FieldsUpdater::hit(int x, int y) {
	lastHit_ = std::make_pair(x,y);
	oponent_->getGameboard()->hit(x,y);
}

FieldsUpdater::FieldType FieldsUpdater::getLastHit() const{
	return lastHit_;
}

void FieldsUpdater::shipsNotHit(int x,int y){
	player_->getOutput()->oponentMissHit(lastHit_.first,lastHit_.second);
	oponent_->getOutput()->playerMissHit(lastHit_.first,lastHit_.second);
}
