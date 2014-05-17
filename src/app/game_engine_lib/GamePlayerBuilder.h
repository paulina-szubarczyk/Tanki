/*
 * GamePlayerBuilder.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEPLAYERBUILDER_H_
#define GAMEPLAYERBUILDER_H_

#include "PlayerBuilder.h"

class GamePlayerBuilder : public PlayerBuilder {
public:
	typedef std::shared_ptr<BigGameShip> ShipPtr;

	GamePlayerBuilder();
	virtual ~GamePlayerBuilder();

	virtual void addPlayerGameboard(int size);
	virtual GamePlayer* configPlayerFieldsUpdater(GamePlayer* firstPlayer, GamePlayer* secondPlayer_);
	virtual void addPlayerConnection(std::shared_ptr<ships::ProtobufConnection> connection) ;
	virtual void addPlayerShips(std::vector<std::vector<int>> y,
								std::vector<std::vector<int>> x) ;
	virtual void addPlayerShip( std::vector<int> x,
								std::vector<int> y) ;

};

#endif /* GAMEPLAYERBUILDER_H_ */
