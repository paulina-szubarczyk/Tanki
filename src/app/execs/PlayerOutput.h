/*
 * PlayerOutput.h
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#ifndef PLAYEROUTPUT_H_
#define PLAYEROUTPUT_H_
#include "IPlayerOutput.h"
#include "ProtobufConnection.h"
#include "message.pb.h"

class PlayerOutput : public game::IPlayerOutput{
	typedef std::shared_ptr<DataMsg> MsgPtr;
public:
	PlayerOutput(std::shared_ptr<ships::ProtobufConnection> connection);
	virtual ~PlayerOutput() = default;

	virtual void beginGame()  ;
	virtual void playerTurn()  ;
	virtual void playerShipHit(int x, int y) ;
	virtual void playerShipSunk(int x, int y) ;
	virtual void playerMissHit(int x, int y) ;
	virtual void oponentShipHit(int x, int y) ;
	virtual void oponentShipSunk(int x, int y) ;
	virtual void oponentMissHit(int x, int y) ;
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
		std::shared_ptr<ships::ProtobufConnection> connection_;
		MsgPtr createMsg() const {
			return MsgPtr(new DataMsg());
		}
};

#endif /* PLAYEROUTPUT_H_ */
