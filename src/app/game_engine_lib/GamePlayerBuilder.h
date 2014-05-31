/*
 * GamePlayerBuilder.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYERBUILDER_H_
#define GAMEPLAYERBUILDER_H_

#include "PlayerBuilder.h"
#include "FieldsUpdater.h"

class GamePlayerBuilder : public PlayerBuilder {
public:
	typedef std::shared_ptr<BigGameShip> ShipPtr;
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

	GamePlayerBuilder();
	virtual ~GamePlayerBuilder();

	void createGamePlayer(OutputPtr output);
	virtual void addPlayerGameboard(int size);
	virtual void addPlayerShips(std::vector<std::vector<int>> y,
								std::vector<std::vector<int>> x) ;

	virtual void addPlayerShip( std::vector<int> x,
								std::vector<int> y) ;
	static void configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2);
protected:

};

#endif /* GAMEPLAYERBUILDER_H_ */
