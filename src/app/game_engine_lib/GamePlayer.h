/*
 * GamePlayer.h
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYER_H_
#define GAMEPLAYER_H_

#include <vector>
#include <memory>

namespace game {

class Gameboard;
class IPlayerOutput;
class Game;
class BigGame;
class FieldsUpdater;
class Gameboard;
class IPlayerOutput;
class BigShip;

class GamePlayer {
	friend class PlayerFactory;
public:

	typedef std::shared_ptr<Gameboard> GameboardPtr;
	typedef	std::shared_ptr<IPlayerOutput> OutputPtr;
	typedef std::shared_ptr<FieldsUpdater> FieldsUpdaterPtr;

	GamePlayer(OutputPtr output);
	virtual ~GamePlayer() = default;

	void hitField(int x, int y);
	void shipsAdded() ;
	bool isHit() const ;
	bool isTurn() const ;

	OutputPtr getOutput() const ;
	FieldsUpdaterPtr getFieldsUpdater() ;
	std::shared_ptr<Game> getGame() const;
	GameboardPtr getGameboard() const;
	std::vector<std::shared_ptr<BigShip> >& getShips() ;

	void setFieldsUpdater(const FieldsUpdaterPtr& fieldsUpdater) ;
	void setShips(const std::vector<std::shared_ptr<BigShip> >& ships) ;
	void setGameboard(GameboardPtr gameboard) ;
	void setTurn(bool turn);
	void setGame(std::shared_ptr<Game> game) ;
	void setHit(bool hit) ;


private:
	std::vector<std::shared_ptr<BigShip>> ships_;
	GameboardPtr gameboard_;
	FieldsUpdaterPtr fieldsUpdater_;
	OutputPtr output_;
	std::shared_ptr<Game> game_;
	bool turn_;
	bool hit_;
};
}
#endif /* GAMEPLAYER_H_ */
