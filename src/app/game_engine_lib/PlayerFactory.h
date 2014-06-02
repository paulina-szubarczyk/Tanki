/*
 * PlayerFactory.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYERBUILDER_H_
#define GAMEPLAYERBUILDER_H_

#include "FieldsUpdater.h"

namespace game {

class IPlayerOutput;
class BigShip;

typedef std::shared_ptr<IPlayerOutput> OutputPtr;
class PlayerFactory {
public:
	typedef std::shared_ptr<BigShip> ShipPtr;
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

	PlayerFactory() = delete;
	virtual ~PlayerFactory() = delete;

	static PlayerPtr createGamePlayer(OutputPtr output);
	static void addPlayerGameboard(PlayerPtr player, int size);


	static void addPlayerShips(PlayerPtr player, std::vector<std::vector<int>> y,
								std::vector<std::vector<int>> x) ;

	static void addPlayerShip(PlayerPtr player, std::vector<int> x,
								std::vector<int> y);

	static void configPlayerFieldsUpdater(PlayerPtr player1, PlayerPtr player2);
};
}
#endif /* GAMEPLAYERBUILDER_H_ */
