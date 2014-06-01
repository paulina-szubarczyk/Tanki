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
#include "Game.h"
#include <vector>

class GamePlayer {
	friend class GamePlayerBuilder;
public:
	typedef std::shared_ptr<FieldsUpdater> FieldsUpdaterPtr;
	GamePlayer(OutputPtr output);
	virtual ~GamePlayer() = default;

	void hitField(int x, int y);

	const OutputPtr& getOutput() const {
		return output_;
	}

	FieldsUpdaterPtr& getFieldsUpdater()  {
		return fieldsUpdater_;
	}

	void setFieldsUpdater(const FieldsUpdaterPtr& fieldsUpdater) {
		fieldsUpdater_ = fieldsUpdater;
	}

	std::vector<std::shared_ptr<BigGameShip> >& getShips()  {
		return ships_;
	}

	void setShips(const std::vector<std::shared_ptr<BigGameShip> >& ships) {
		ships_ = ships;
	}

	GameboardPtr getGameboard() const{
		return gameboard_;
	}

	void setGameboard(GameboardPtr gameboard) {
			gameboard_ = gameboard;;
		}

	bool isTurn() const {
		return turn_;
	}

	void setTurn(bool turn);

	void shipsAdded() ;

	std::shared_ptr<Game> getGame() const {
		return game_;
	}

	void setGame(std::shared_ptr<Game> game) {
		game_ = game;
	}

	bool isHit() const {
		return hit_;
	}

	void setHit(bool hit) {
		hit_ = hit;
	}

private:
	std::vector<std::shared_ptr<BigGameShip>> ships_;
	GameboardPtr gameboard_;
	FieldsUpdaterPtr fieldsUpdater_;
	OutputPtr output_;
	std::shared_ptr<Game> game_;
	bool turn_;
	bool hit_;
};

#endif /* GAMEPLAYER_H_ */
