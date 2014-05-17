/*
 * GamePlayerBuilder.h
 *
 *  Created on: May 15, 2014
 *      Author: paulina
 */

#ifndef PLAYERBUILDER_H_
#define PLAYERBUILDER_H_

#include "ShipFactoryMethod.h"
#include "GamePlayer.h"
#include "ProtobufConnection.h"


class PlayerBuilder {
public:
	PlayerBuilder();
	virtual ~PlayerBuilder();

	void createPlayer() {player_ = new GamePlayer();};
	GamePlayer* getPlayer() {return player_;};
	virtual void addPlayerGameboard(int size) = 0;
	virtual GamePlayer* configPlayerFieldsUpdater(GamePlayer*,GamePlayer*) = 0;
	virtual void addPlayerConnection(std::shared_ptr<ships::ProtobufConnection> connection) = 0;
	virtual void addPlayerShips(std::vector<std::vector<int>> y,
						std::vector<std::vector<int>> x) = 0;
	virtual void addPlayerShip( std::vector<int> x,
						std::vector<int> y) = 0;

protected:
	GamePlayer* player_;
	ShipFactoryMethod* shipFactory;
};

#endif /* PLAYERBUILDER_H_ */
