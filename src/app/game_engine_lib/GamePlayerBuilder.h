/*
 * GamePlayerBuilder.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYERBUILDER_H_
#define GAMEPLAYERBUILDER_H_

#include "FieldsUpdater.h"

class PlayerOutput;
class BigGameShip;

class GamePlayerBuilder {
public:
	typedef std::shared_ptr<BigGameShip> ShipPtr;
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

	GamePlayerBuilder() = delete;
	virtual ~GamePlayerBuilder() = delete;

	static PlayerPtr createGamePlayer(OutputPtr output);
	static void addPlayerGameboard(PlayerPtr player, int size);


	static void addPlayerShips(PlayerPtr player, std::vector<std::vector<int>> y,
								std::vector<std::vector<int>> x) ;

	static void addPlayerShip(PlayerPtr player, std::vector<int> x,
								std::vector<int> y);

	static void configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2);
};

#endif /* GAMEPLAYERBUILDER_H_ */
