/*
 * PlayerOutput.h
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#ifndef PLAYEROUTPUT_H_
#define PLAYEROUTPUT_H_
#include "GamePlayerOutput.h"
#include "Connection.h"
class PlayerOutput : public GamePlayerOutput{
public:
	PlayerOutput(std::shared_ptr<ships::Connection> connection);
	virtual ~PlayerOutput();

	virtual void getShips() ;
	virtual void beginGame()  ;
	virtual void playerTurn()  ;
	virtual void playerShipHit(int x, int y) ;
	virtual void playerShipSunk(int x, int y) ;
	virtual void oponentShipHit(int x, int y) ;
	virtual void oponentShipSunk(int x, int y) ;
	virtual void oponentWin() ;
	virtual void playerWin() ;

	/** error code methods
	 *
	 */
	virtual void gameAlreadyOccupied();
	virtual void notEnoughShips(int delivered, int expected) ;
	virtual void playerNotReady() ;
	virtual void oponentNotReady();
	virtual void oponentTurn();

	private:
		std::shared_ptr<ships::Connection> connection_;
};

#endif /* PLAYEROUTPUT_H_ */
