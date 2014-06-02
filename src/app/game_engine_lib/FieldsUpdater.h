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
/**
 * Class which interact with Gameboard fields
 * Observ oponent ship. Registered in GamePlayerBuilder::configFieldsUpdater
 */
namespace game {

class GamePlayer;
class FieldsUpdater: public ShipObserver {
	typedef	std::shared_ptr<GamePlayer> PlayerPtr;
public:
	FieldsUpdater(PlayerPtr player1, PlayerPtr player2);
	FieldsUpdater();
	virtual ~FieldsUpdater();

	/// ship observer method, call after oponent ship hit in calling output method
	virtual void shipHit(IShip::ShipState state) override;

	typedef std::pair<int,int> FieldType;

	/// method call by player to send his move
	void hit(int x, int y);
	/// is used to check which field was hit
	FieldType getLastHit() const;

	/// method call when empty field was hitten, in calling output method
	void shipsNotHit(int x,int y);
private:
	FieldType lastHit_;
	PlayerPtr oponent_;
	PlayerPtr player_;
};
}
#endif /* CLIENTFIELDUPDATER_H_ */
