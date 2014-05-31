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

class GamePlayer;
class FieldsUpdater: public ShipObserver {
	typedef	std::shared_ptr<GamePlayer> PlayerPtr;
public:
	FieldsUpdater(PlayerPtr player1, PlayerPtr player2);
	FieldsUpdater();
	virtual ~FieldsUpdater();

	virtual void shipHit(GameShip::ShipState state) override;

	typedef std::pair<int,int> FieldType;


	void hit(int x, int y);
	FieldType getLastHit() const;

private:
	FieldType lastHit_;
	PlayerPtr oponent_;
	PlayerPtr player_;
};

#endif /* CLIENTFIELDUPDATER_H_ */
