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
	typedef std::shared_ptr<GamePlayer> PlayerPtr;

	GamePlayerBuilder(ProtobufConnPtr connection);
	virtual ~GamePlayerBuilder();

	void createGamePlayer();
	virtual void addPlayerConnection(std::shared_ptr<ships::ProtobufConnection> connection) ;
	virtual void addPlayerMsgHandler() ;
	virtual void addPlayerMsgSender() ;
	virtual void addPlayerGameboard(int size);
	virtual void addPlayerShips(std::vector<std::vector<int>> y,
								std::vector<std::vector<int>> x) ;

	virtual void addPlayerShip( std::vector<int> x,
								std::vector<int> y) ;
	static void configPlayerFieldsUpdater(PlayerPtr firstPlayer, PlayerPtr secondPlayer_);
protected:
	bool shipsError_;
};

#endif /* GAMEPLAYERBUILDER_H_ */
