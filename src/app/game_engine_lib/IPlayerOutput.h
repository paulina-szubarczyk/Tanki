/*
 * GameOutput.h
 *
 *  Created on: May 17, 2014
 *      Author: paulina
 */

#ifndef GAMEOUTPUT_H_
#define GAMEOUTPUT_H_
namespace game {
class IPlayerOutput {
public:
	IPlayerOutput() = default;
	virtual ~IPlayerOutput() = default;

	virtual void beginGame() = 0 ;
	virtual void playerTurn() = 0 ;
	virtual void playerShipHit(int x, int y) = 0;
	virtual void playerShipSunk(int x, int y) = 0;
	virtual void playerMissHit(int x, int y) = 0;
	virtual void oponentShipHit(int x, int y) = 0;
	virtual void oponentShipSunk(int x, int y) = 0;
	virtual void oponentMissHit(int x, int y) = 0;
	virtual void oponentWin() = 0;
	virtual void playerWin() = 0;

	/** error code methods
	 *
	 */
	virtual void gameAlreadyOccupied() = 0;
	virtual void notEnoughShips(int delivered, int expected) = 0;
	virtual void playerNotReady() = 0;
	virtual void oponentNotReady() = 0;
	virtual void oponentTurn() = 0;
};
}
#endif /* GAMEOUTPUT_H_ */
