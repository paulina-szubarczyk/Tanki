/*
 * GamePlayer.h
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYER_H_
#define GAMEPLAYER_H_

#include "BigGameShip.h"
#include "gameEngine_typedef.h"
#include "FieldsUpdater.h"

#include <vector>
class GamePlayer {
	friend class GamePlayerBuilder;
public:
	typedef std::shared_ptr<FieldsUpdater> FieldsUpdaterPtr;
	GamePlayer(OutputPtr output);
	virtual ~GamePlayer();

	void hitField(int x, int y);
	void changeTurn(bool turn);
	bool getTurn();
	GameboardPtr getGameboard();

private:
	std::vector<std::shared_ptr<BigGameShip>> ships_;
	GameboardPtr gameboard_;
	FieldsUpdaterPtr fieldsUpdater_;
	OutputPtr output_;
	bool turn_;
};

#endif /* GAMEPLAYER_H_ */
